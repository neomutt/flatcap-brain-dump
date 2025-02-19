// gcc -I. -o maildir-find-uid maildir-find-uid.c

#include <stdio.h>
#include <string.h>

const char *MaildirFieldDelimiter = ":";

static const char *cc_maildir_field_delimiter(void)
{
  return MaildirFieldDelimiter;
}

static size_t mutt_str_len(const char *a)
{
  return a ? strlen(a) : 0;
}

static void maildir_find_uid(const char *filename, short *uid_start, short *uid_length)
{
  if (*uid_length > 0) // Already calculated
    return;

  const char *base = filename;
  const char *slash = strrchr(filename, '/');
  if (slash)
    base = slash + 1;

  *uid_start = (short) (base - filename);

  const char c_maildir_field_delimiter = *cc_maildir_field_delimiter();

  char end_chars[8] = { 0 };
  snprintf(end_chars, sizeof(end_chars), ",%c", c_maildir_field_delimiter);
  char *end = strpbrk(base, end_chars);

  if (end)
    *uid_length = (short) (end - base);
  else
    *uid_length = (short) mutt_str_len(base);
}

int main(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    short uid_start = 0;
    short uid_length = 0;

    maildir_find_uid(argv[i], &uid_start, &uid_length);
    printf("%s\n", argv[i]);
    printf("%*s%.*s\n", (int) uid_start, "", (int) uid_length, argv[i] + uid_start);
    printf("\n");
    printf("start  = %hd\n", uid_start);
    printf("length = %hd\n", uid_length);
    printf("\n");
  }

  return 0;
}
