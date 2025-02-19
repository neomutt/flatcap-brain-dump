// gcc -I. -o maildir-parse-flags maildir-parse-flags.c libmutt.a -lpcre2-8

#include "config.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mutt/lib.h"

const char *MaildirFieldDelimiter = ":";

// clang-format off
typedef uint8_t MaildirFlags;      ///< Maildir filename flags, e.g. #MD_MF_FLAGGED
#define MD_MF_NO_FLAGS          0  ///< No flags are set
#define MD_MF_FLAGGED     (1 << 0) ///< Email is flagged
#define MD_MF_REPLIED     (1 << 1) ///< Email has been replied to
#define MD_MF_SEEN        (1 << 2) ///< Email has been seen
#define MD_MF_TRASHED     (1 << 3) ///< Email is marked as deleted
// clang-format on

static const char *cc_maildir_field_delimiter(void)
{
  return MaildirFieldDelimiter;
}

static MaildirFlags maildir_parse_flags2(const char *path, char **custom)
{
  const char c_maildir_field_delimiter = *cc_maildir_field_delimiter();
  char *p = strrchr(path, c_maildir_field_delimiter);
  if (!p)
    return MD_MF_NO_FLAGS;

  if (!mutt_str_startswith(p + 1, "2,"))
    return MD_MF_NO_FLAGS;

  p += 3;

  MaildirFlags flags = MD_MF_NO_FLAGS;

  char leftover[16] = { 0 };
  int num = 0;

  for (; *p; p++)
  {
    switch (*p)
    {
      case 'F':
        flags |= MD_MF_FLAGGED;
        break;

      case 'R':
        flags |= MD_MF_REPLIED;
        break;

      case 'S':
        flags |= MD_MF_SEEN;
        break;

      case 'T':
        flags |= MD_MF_TRASHED;
        break;

      default:
        leftover[num++] = *p;
        break;
    }
  }

  if (custom)
    *custom = mutt_str_dup(leftover);

  return flags;
}

int main(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    char *custom = NULL;

    MaildirFlags flags = maildir_parse_flags2(argv[i], &custom);
    printf("%s\n", argv[i]);
    printf("\t%s%s%s%s, %s\n", (flags & MD_MF_FLAGGED) ? "F" : "",
           (flags & MD_MF_REPLIED) ? "R" : "", (flags & MD_MF_SEEN) ? "S" : "",
           (flags & MD_MF_TRASHED) ? "T" : "", NONULL(custom));
    printf("\n");
  }

  return 0;
}
