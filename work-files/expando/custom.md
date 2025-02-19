## Custom Nodes

If an `struct ExpandoDefinition` has a custom parser, it may return a custom `ExpandoNode`, with a custom child.

### Custom

```c
struct ExpandoNode
{
  ENT_CUSTOM;
};
```

```c
struct ExpandoNodeMyType
{
  const char *data1;
  int         value2;
};
```

### Tree/Subject Splitting

`$index_format`s `%s` expando contains two parts: tree characters and the subject.

If we introduce a custom parser, we could split this in two using a Container node.

- `Container { Expando-for-tree-chars, Expando-for-subject }`

