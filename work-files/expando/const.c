#include <stddef.h>
#include <stdio.h>

struct Buffer
{
  char buf[32];
};

struct Node
{
  int num;
  struct Buffer *b1;
  struct Buffer b2;
};

void function(const struct Node *n)
{
  // n->num = 42;
  // n->b1 = NULL;
  n->b1->buf[0] = 'j';
  // n->b2.buf[0] = 'm';
}

int main()
{
  struct Buffer b1 = { "hello" };
  struct Node n = { 42, &b1, { "world" } };
  function(&n);

  printf("%s, %s\n", n.b1->buf, n.b2.buf);
  return 0;
}
