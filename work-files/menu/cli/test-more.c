#include <stdio.h>
#include <unistd.h>
#include "mutt/lib.h"
#include "cli/lib.h"

int endwin(void)
{
  return 0;
}

static void args_clear(struct StringArray *sa)
{
  char **cp = NULL;
  ARRAY_FOREACH(cp, sa)
  {
    FREE(cp);
  }

  ARRAY_FREE(sa);
}

bool is_arg(const char *str)
{
  if (str[0] == '\0')
    return true;

  return ((str[0] != '-') || (str[1] == '\0'));
}

int mop_up(int argc, char **argv, int index, struct StringArray *sa)
{
  int count = 0;
  for (int i = index; i < argc; i++, count++)
  {
    if (!is_arg(argv[i]))
      break;

    ARRAY_ADD(sa, mutt_str_dup(argv[i]));
  }

  return count;
}

int main(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    printf("%d  %c  %s\n", i, is_arg(argv[i]) ? 'Y' : 'N', argv[i]);
  }
  printf("\n");

  printf("-------------------\n\n");

  struct StringArray aa = ARRAY_HEAD_INITIALIZER;
  struct StringArray qa = ARRAY_HEAD_INITIALIZER;

  int count = mop_up(argc, argv, 1, &aa);
  printf("\033[1;36m%d leading args\033[0m\n", count);
  char **cp = NULL;
  ARRAY_FOREACH(cp, &aa)
  {
    printf("\t'%s'\n", NONULL(*cp));
  }
  printf("\n");

  argc -= count;
  argv += count;

  printf("-------------------\n\n");

  bool rc = true;
  opterr = 0;
  while ((optind < argc) && rc)
  {
    int opt = getopt(argc, argv, "+A:a:b:Cc:Dd:Ee:F:f:Gg:hH:i:l:m:nOpQ:RSs:TvyZz");

    switch (opt)
    {
      case 'Q':
      {
        printf("\033[1;32moption\033[0m\n");
        printf("\topt = %c\n", opt);
        printf("\toptarg = '%s\n", optarg);
        ARRAY_ADD(&qa, mutt_str_dup(optarg));
        count = mop_up(argc, argv, optind, &qa);
        printf("\tcount = %d\n", count + 1);
        optind += count;
        break;
      }

      case 'v':
        break;

      case -1:
      {
        printf("\033[1;33mend of options\033[0m\n");
        printf("\topt = -1\n");
        for (int i = optind; i < argc; i++)
        {
          ARRAY_ADD(&aa, mutt_str_dup(argv[i]));
        }
        printf("\t%d end options\n", argc - optind);
        optind = argc;
        break;
      }

      default:
      {
        printf("\033[1;31merror\033[0m\n");
        printf("\topt = %c\n", opt);
        printf("\toptopt = %c\n", optopt);
        printf("\toptind = \033[1;31m%s\033[0m (%d)\n", argv[optind], optind);
        rc = false;
      }
    }
    printf("\n");
  }

  if (rc)
  {
    printf("-------------------\n\n");
    printf("Addresses (%d):\n", ARRAY_SIZE(&aa));
    ARRAY_FOREACH(cp, &aa)
    {
      printf("\t'%s'\n", NONULL(*cp));
    }
    printf("\n");

    printf("Queries (%d):\n", ARRAY_SIZE(&qa));
    ARRAY_FOREACH(cp, &qa)
    {
      printf("\t'%s'\n", NONULL(*cp));
    }
    printf("\n");
  }

  args_clear(&aa);
  args_clear(&qa);
  return 0;
}
