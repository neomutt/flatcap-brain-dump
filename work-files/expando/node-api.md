## Expando Node

Upgrade `ExpandoNode` to have an API.

We want to be able to render the string, test for "true-ness" and possibly generate a new format string.

```c
struct ExpandoNode
{
  enum ExpandoNodeType type;
  struct ExpandoNode  *next;

  void *ndata;
  void (*ndata_free)(void **ptr);

  /**
   * render - Render an Expando
   * @param[in]  node      ExpandoNode to format
   * @param[in]  max_width Number of screen columns
   * @param[in]  flags     Flags, see #MuttFormatFlags
   * @param[out] buf       Buffer for the result
   * @retval num Number of bytes written to buf
   *
   * Each callback function implements some expandos, e.g.
   *
   * | Expando | Description
   * | :------ | :----------
   * | \%t     | Title
   */
  int (*render)(const struct ExpandoNode *node, int max_width, MuttFormatFlags flags, struct Buffer *buf);

  /**
   * is_true - Test a conditional Expando
   * @param[in]  node      ExpandoNode to test
   * @retval true Expando condition is true
   */
  bool (*is_true)(const struct ExpandoNode *node);

  /**
   * generate - Create a new format string
   * @param[in]  node ExpandoNode to formay
   * @param[out] buf  Buffer for the result
   * @retval num Number of bytes written to buf
   */
  int (*generate)(const struct ExpandoNode *node, struct Buffer *buf);
};
```

- `render()`
  Allow the expando code to render nodes without knowing what type they are.

- `is_true()`
  Many expandos can be used conditionally.
  e.g. Numbers that are greater than zero; Strings that are non-empty
  A dedicated test function allows us to delegate the tricky cases, like conditional dates.

- `generate()` - In the future
  Generate a format string from the Node tree.
  Many programs allow you to tweak the order and size of table columns.
