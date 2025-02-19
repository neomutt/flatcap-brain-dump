## Expando Types

Empty, Text, Expando, Padding, Conditional, Conditional Date, Container.

Strip down `ExpandoNode` to:

```c
struct ExpandoNode
{
  enum ExpandoNodeType type;
  struct ExpandoNode  *next;

  void *ndata;
  void (*ndata_free)(void **ptr);
};
```

Each node type has its own ndata.

### Empty

No private data :-)

### Text

```c
struct ExpandoNodeText
{
  const char *start;
  const char *end;
};
```

### Padding

```c
struct ExpandoNodePad
{
  enum ExpandoPadType pad_type;
  char                pad_char;
}:
```

### Conditional

```c
struct ExpandoNodeConditional
{
  struct ExpandoNode *condition;
  struct ExpandoNode *if_true_tree;
  struct ExpandoNode *if_false_tree;
};
```

### Conditional Date

```c
struct ExpandoNodeConditionalDate
{
  int    count;
  char   period;
  time_t multiplier;
};
```

### Container

```c
struct ExpandoNodeContainer
{
  struct ExpandoNode *children;
};
```

