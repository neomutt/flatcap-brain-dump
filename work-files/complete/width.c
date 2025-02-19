#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  setlocale(LC_ALL, "");
  const char *str = argv[1];

  size_t bytes = strlen(str);
  size_t len = mbrtowc(NULL, str, bytes, NULL);

  printf("str   = %s\n", str);
  printf("bytes = %ld\n", bytes);
  printf("len   = %ld\n", len);
  printf("error = %d: %s\n", errno, strerror(errno));
  return 0;
}
