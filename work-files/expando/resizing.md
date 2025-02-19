## Resizing Nodes

There are over 200 expando callbacks.
Most of them need to do some form of formatting.

The render function knows how much space is available, so it makes sense for it to do the formatting.

### Simplify the callbacks

```c
int index_L(const struct ExpandoNode *node, char *buf, int buf_len, int cols_len, void *data, MuttFormatFlags flags)
{
  assert(node->type == ENT_EXPANDO);

  const struct HdrFormatInfo *hfi = data;
  const struct Email *e = hfi->email;

  char fmt[128] = { 0 };
  char tmp[128] = { 0 };

  make_from(e->env, tmp, sizeof(tmp), true, flags);
  format_string(fmt, sizeof(fmt), tmp, flags, MT_COLOR_INDEX_AUTHOR,
                MT_COLOR_INDEX, node, NO_TREE);
  return snprintf(buf, buf_len, "%s", fmt);
}
```

might become:

```c
int index_L(const struct ExpandoNode *node, MuttFormatFlags flags, struct Buffer *buf)
{
  assert(node->type == ENT_EXPANDO);

  const struct HdrFormatInfo *hfi = node->ndata;
  const struct Email *e = hfi->email;

  return make_from(e->env, buf, true, flags);
}
```

### Resizing all the Nodes

Many Windows in NeoMutt are dynamically sized.
They can be MINIMISE, FIXED or MAXIMISE.
Each requests an amount of space and the reflow functions allocate it fairly.

The Expandos could be a simpler version of the Windows.

The first pass would be to collect all the strings into Nodes.

- `%a%b%* %c` -> `apple` + `banana` + Pad-space + `cherry`

We have some Padding, so we'll need to check the available space.
There's enough room for `%a`, but not all of `%b`, so we get:

- `apple` + `bana` + Pad-space + `cherry`

which renders to:

- `applebanacherry`

With colours that might be:

- `[+a]apple[-a][+b]bana[-b][+c]cherry[-c]`

