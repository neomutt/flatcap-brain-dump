# Review: `ParseFlag` / `ParseFlags`

```c
/**
 * enum ParseFlag - Flags affecting parsing behavior
 */
enum ParseFlag
{
  PC_NONE       = 0,      ///< No flags
  PC_GUI_ACTIVE = 1 << 0, ///< GUI is active
};
typedef uint8_t ParseFlags;
```

## Observations

### 1. Underlying type mismatch risk

`enum ParseFlag` is implementation-defined in size and signedness, while `ParseFlags` is explicitly `uint8_t`.

This can lead to:

- implicit narrowing conversions
- compiler warnings under stricter flags
- accidental overflow if additional flags exceed 8 bits

The declaration currently relies on a convention rather than a type guarantee.

## Recommended patterns

### Option A: Keep the enum, derive the storage type

If the project has a helper macro or convention for enum bitmasks, prefer deriving the flag container from the enum:

```c
enum ParseFlag
{
  PC_NONE       = 0,
  PC_GUI_ACTIVE = 1 << 0,
};

typedef unsigned int ParseFlags;
```

This is the most idiomatic C approach unless compact storage is specifically required.

---

### Option B: Make the bit width explicit

If compact 8-bit storage is intentional, document and enforce the constraint:

```c
enum ParseFlag
{
  PC_NONE       = 0,
  PC_GUI_ACTIVE = 1 << 0,
};

typedef uint8_t ParseFlags;

static_assert(PC_GUI_ACTIVE <= UINT8_MAX, "ParseFlag exceeds ParseFlags width");
```

For C11:

```c
_Static_assert(PC_GUI_ACTIVE <= UINT8_MAX,
               "ParseFlag exceeds ParseFlags width");
```

This becomes increasingly valuable as more flags are added.

---

### Option C: Use a dedicated flag macro system

If NeoMutt already has a flag-definition pattern elsewhere, consistency is probably more important than local optimisation.

Projects with many flag enums often standardise on helpers such as:

```c
#define FLAG(x) (1U << (x))
```

or typed wrappers/macros for bit operations.

## Naming

The names are clear and conventional.

Minor possible refinement:

```c
PC_HAS_GUI
```

or

```c
PC_GUI
```

depending on whether the flag means:

- GUI subsystem exists
- GUI parsing mode enabled
- parser currently running under GUI context

`ACTIVE` is slightly ambiguous temporally.

## Bit-shift style

Prefer unsigned literals for flag definitions:

```c
PC_GUI_ACTIVE = 1U << 0,
```

This avoids signed-shift edge cases as additional bits are introduced.

## Documentation

The doc comment is good, but the semantic scope of the flags could be clearer.

For example:

```c
/**
 * enum ParseFlag - Runtime modifiers affecting parser behavior
 */
```

or:

```c
/**
 * enum ParseFlag - Context flags for config parsing
 */
```

if parsing refers specifically to configuration parsing.

## Suggested final form

```c
/**
 * enum ParseFlag - Context flags for config parsing
 */
enum ParseFlag
{
  PC_NONE       = 0,
  PC_GUI_ACTIVE = 1U << 0,
};

typedef uint8_t ParseFlags;

_Static_assert(PC_GUI_ACTIVE <= UINT8_MAX,
               "ParseFlag exceeds ParseFlags width");
```

This preserves the compact storage optimisation while making the constraint explicit and future-safe.

