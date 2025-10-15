#include <stdio.h>
#include "mutt/array.h"
#include "mutt/logging2.h"

struct Thing
{
  int apple;
  int banana;
  int cherry;
};

ARRAY_HEAD(ThingArray, struct Thing);

log_dispatcher_t MuttLogger = NULL;

void mutt_exit(int code)
{
  if (code)
  {
  }
}

int main()
{
  struct ThingArray ta = ARRAY_HEAD_INITIALIZER;

  struct Thing one = { 1, 10, 100 };
  struct Thing two = { 2, 20, 200 };
  struct Thing three = { 3, 30, 300 };

  ARRAY_ADD(&ta, one);
  ARRAY_ADD(&ta, two);
  ARRAY_ADD(&ta, three);

  struct Thing *t = NULL;
  ARRAY_FOREACH(t, &ta)
  {
    printf("%d,%d,%d\n", t->apple, t->banana, t->cherry);
  }

  ARRAY_FREE(&ta);
  return 0;
}
