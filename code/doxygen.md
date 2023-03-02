# Doxygen Comments

Formatted Comment Blocks

[Doxygen](http://www.doxygen.nl/) reads specially formatted
comment blocks and turns them into documentation.

The Doxygen
[documentation](http://www.doxygen.nl/manual/commands.html)
lists all the possible commands. Some common ones are:

- **`@param`**   -- a function parameter
- **`@struct`**  -- a C-struct
- **`@union`**   -- a union
- **`@enum`**    -- an enumeration type
- **`@var`**     -- a variable or typedef or enum value
- **`@def`**     -- a #define
- **`@typedef`** -- a type definition
- **`@file`**    -- a file

@a Argument
@image Include an image
@note
@param
@pre
@retval
@sa
@warning

@defgroup
@extends
@ingroup
@mainpage
@page
@ref
@subpage

## Functions

Here's a basic template for a function comment. It begins with two asterisks.

```
/**
 * FUNCTION-NAME - ONE LINE DESCRIPTION OF FUNCTION
 * @param NAME1 SHORT-DESC
 * @param NAME2 SHORT-DESC
 * ...
 *
 * @retval DESC-OF-RETURN-VALUE
 *
 * LONG DESCRIPTION
 */
```

The `@param` can have an optional suffix indicating the direction:

- `[in]`  -- a normal inbound parameter
- `[out]` -- an "out-param" (a value passed to the caller)

```
/**
 * Turn a number into text
 * @param[in]  num  Number to be converted
 * @param[out] ptr  Where to store the new string
 *
```

The return value `@return` could be descriptive, e.g. "Number of apples", or
a list of possible values.

Here, we have XXX inserted and extra `*` to make the text into a list (in
Markdown).

```
 *
 * @retval  0:  Error
 * @retval  n:  Success
 *
```

Here's an example function comment block from `sidebar.c`:

```
/**
 * draw_divider - Draw a line between the sidebar and the rest of neomutt
 * @param wdata    Sidebar data
 * @param win      Window to draw on
 * @param num_rows Height of the Sidebar
 * @param num_cols Width of the Sidebar
 * @retval 0   Empty string
 * @retval num Character occupies n screen columns
 *
 * Draw a divider using characters from the config option "sidebar_divider_char".
 * This can be an ASCII or Unicode character.
 * We calculate these characters' width in screen columns.
 *
 * If the user hasn't set $sidebar_divider_char we pick a character for them,
 * respecting the value of $ascii_chars.
 */
static int draw_divider(struct SidebarWindowData *wdata, struct MuttWindow *win, int num_rows, int num_cols)
```

