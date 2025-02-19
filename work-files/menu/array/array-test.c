#include <stdio.h>
#include "mutt/array.h"
// #include "a2.h"

void show_backtrace(void)
{
}

int endwin(void)
{
  return 0;
}

struct Test
{
  int num;
};
ARRAY_HEAD(TestArray, struct Test);

int main()
{
  struct TestArray ta = ARRAY_HEAD_INITIALIZER;

  struct Test t = { 0 };
  for (int i = 0; i < 10; i++)
  {
    t.num = (17 + (73 * i)) % 13;
    ARRAY_ADD(&ta, t);
  }

  struct Test *tp = NULL;

  printf("\n");
  printf("ARRAY_FOREACH\n");
  ARRAY_FOREACH(tp, &ta)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  printf("ARRAY_FOREACH_FROM(3)\n");
  ARRAY_FOREACH_FROM(tp, &ta, 3)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  printf("ARRAY_FOREACH_TO(7)\n");
  ARRAY_FOREACH_TO(tp, &ta, 7)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  printf("ARRAY_FOREACH_FROM_TO(3,7)\n");
  ARRAY_FOREACH_FROM_TO(tp, &ta, 3, 7)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  printf("ARRAY_FOREACH_FROM_TO(0,10)\n");
  ARRAY_FOREACH_FROM_TO(tp, &ta, 0, 10)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");

  printf("\n");
  printf("ARRAY_FOREACH_REVERSE\n");
  ARRAY_FOREACH_REVERSE(tp, &ta)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  printf("ARRAY_FOREACH_REVERSE_FROM(3)\n");
  ARRAY_FOREACH_REVERSE_FROM(tp, &ta, 3)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  printf("ARRAY_FOREACH_REVERSE_TO(7)\n");
  ARRAY_FOREACH_REVERSE_TO(tp, &ta, 7)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  printf("ARRAY_FOREACH_REVERSE_FROM_TO(7,3)\n");
  ARRAY_FOREACH_REVERSE_FROM_TO(tp, &ta, 7, 3)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  printf("ARRAY_FOREACH_REVERSE_FROM_TO(10,0)\n");
  ARRAY_FOREACH_REVERSE_FROM_TO(tp, &ta, 10, 0)
  {
    // printf("%d: %d\n", ARRAY_FOREACH_IDX_tp, tp->num);
    printf("%d ", ARRAY_FOREACH_IDX_tp);
  }

  printf("\n");
  return 0;
}
