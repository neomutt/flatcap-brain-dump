#include <stdio.h>

int main()
{
  for (int t_start = 0; t_start < 10; t_start++)
  {
    for (int t_end = 0; t_end < 10; t_end++)
    {
      for (int s_start = 0; s_start < 10; s_start++)
      {
        for (int s_end = 0; s_end < 10; s_end++)
        {
          printf("%d%d%d%d: ", t_start, t_end, s_start, s_end);
          if (t_start == t_end)
          {
            printf("T empty\n");
            continue;
          }
          else if (t_start > t_end)
          {
            printf("T negative\n");
            continue;
          }

          if (t_start < s_start)
          {
            printf("T before S, ");
          }
          else if (t_start == s_start)
          {
            printf("T at start of S, ");
          }
          else if ((t_start > s_start) && (t_start < s_end))
          {
            printf("T during S, ");
          }
          else if ((t_start > s_start) && (t_start == s_end))
          {
            printf("T at end of S, ");
          }
          else
          {
            printf("T after S, ");
          }

          if (t_end < s_start)
          {
            printf("t before S, ");
          }
          else if (t_end == s_start)
          {
            printf("t at start of S, ");
          }
          else if ((t_end > s_start) && (t_end < s_end))
          {
            printf("t during S, ");
          }
          else if ((t_end > s_start) && (t_end == s_end))
          {
            printf("t at end of S, ");
          }
          else
          {
            printf("t after S, ");
          }

          if (s_start == s_end)
          {
            printf("S empty\n");
            continue;
          }
          else if (s_start > s_end)
          {
            printf("S negative\n");
            continue;
          }

          if (s_start < t_start)
          {
            printf("S before T, ");
          }
          else if (s_start == t_start)
          {
            printf("S at start of T, ");
          }
          else if ((s_start > t_start) && (s_start < t_end))
          {
            printf("S during T, ");
          }
          else if ((s_start > t_start) && (s_start == t_end))
          {
            printf("S at end of T, ");
          }
          else
          {
            printf("S after T, ");
          }

          if (s_end < t_start)
          {
            printf("s before T, ");
          }
          else if (s_end == t_start)
          {
            printf("s at start of T, ");
          }
          else if ((s_end > t_start) && (s_end < t_end))
          {
            printf("s during T, ");
          }
          else if ((s_end > t_start) && (s_end == t_end))
          {
            printf("s at end of T, ");
          }
          else
          {
            printf("s after T, ");
          }

          printf("\n");
        }
      }
    }
  }

  return 0;
}
