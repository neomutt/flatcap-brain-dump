# Enum Flags vs Macro Flags in C

## Short answer

Yes, non-consecutive enum values are completely normal and idiomatic in C, especially for bitmask flags.

This is common and well-understood:

```c
enum ParseFlag
{
  PC_NONE       = 0,
  PC_GUI_ACTIVE = 1U << 0,
  PC_VERBOSE    = 1U << 1,
  PC_DEBUG      = 1U << 4,
};
```

Sparse values are not a problem.

---

# The real question

The more important design question is:

- should flags be represented by an `enum`
- or by `#define` constants

Both are valid C styles.

## Recommendation

For modern C code, prefer:

```c
enum FooFlag
```

over:

```c
#define FOO_FLAG_X ...
```

unless you specifically need preprocessor semantics.

Enums provide:

- debugger visibility
- compiler diagnostics
- symbol scoping by convention
- easier navigation/search
- cleaner documentation generation
- type grouping

Macros provide none of these.

---

# Recommended pattern

The strongest conventional pattern is:

```c
/**
 * enum ReadLineFlag - Flags for mutt_file_read_line()
 */
enum ReadLineFlag
{
  MUTT_RL_NO_FLAGS = 0,
  MUTT_RL_CONT     = 1U << 0, ///< Backslash continuation
  MUTT_RL_EOL      = 1U << 1, ///< Preserve newline
};

typedef uint8_t ReadLineFlags;
```

This gives:

- symbolic grouping
- compact storage
- debugger-friendly names
- compatibility with bitwise operators

---

# Why projects historically used macros

Older C projects often preferred:

```c
#define FLAG_X ...
```

because:

- pre-ANSI compiler compatibility
- weak enum diagnostics in old compilers
- concern about enum storage size
- heavy macro metaprogramming styles
- kernel-style traditions

Most of those reasons are obsolete for modern codebases.

---

# One subtle advantage of enums

Enums communicate intent.

Compare:

```c
#define MUTT_RL_CONT (1 << 0)
```

versus:

```c
enum ReadLineFlag
{
  MUTT_RL_CONT = 1U << 0,
};
```

The second explicitly says:

"this symbol belongs to a conceptual flag set"

That becomes valuable in large codebases.

---

# Important implementation detail

Always use unsigned shifts:

```c
1U << n
```

not:

```c
1 << n
```

Signed left-shift overflow is problematic once higher bits are introduced.

---

# Naming recommendation

Prefer singular enum names and plural typedef names:

```c
enum ReadLineFlag
```

vs

```c
typedef uint8_t ReadLineFlags;
```

This convention scales extremely well.

Examples:

```c
enum EmailFlag;
typedef uint32_t EmailFlags;

struct ConfigFlag;
typedef uint16_t ConfigFlags;
```

---

# A very clean modern pattern

A particularly maintainable style is:

```c
enum ReadLineFlag
{
  MUTT_RL_NONE = 0,
  MUTT_RL_CONT = 1U << 0,
  MUTT_RL_EOL  = 1U << 1,
};

typedef uint8_t ReadLineFlags;
```

Notes:

- avoid mixing `_NO_FLAGS` and plural names
- `NONE` is shorter and widely recognised
- align naming with the enum concept

---

# When macros are still preferable

Macros still make sense when:

- values must participate in `#if`
- compile-time token concatenation is needed
- generated code depends on preprocessing
- values are shared with assembler/preprocessor contexts
- you need portable constant-expression tricks across compilers

Otherwise, enums are usually superior.

---

# Final recommendation

For NeoMutt-style code, the enum + compact typedef approach is likely the best balance:

```c
/**
 * enum ReadLineFlag - Flags for mutt_file_read_line()
 */
enum ReadLineFlag
{
  MUTT_RL_NONE = 0,
  MUTT_RL_CONT = 1U << 0,
  MUTT_RL_EOL  = 1U << 1,
};

typedef uint8_t ReadLineFlags;
```

It is clearer, more maintainable, and more self-documenting than the macro form.

