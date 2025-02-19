#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *_(const char *message)
{
  return message;
}

void mutt_error(const char *message)
{
  printf("%s\n", message);
}

void mutt_exit(int code)
{
  exit(code);
}

void mutt_mem_free(void *ptr)
{
  if (!ptr)
    return;
  void **p = (void **) ptr;
  if (*p)
  {
    free(*p);
    *p = NULL;
  }
}

void mutt_mem_realloc(void *ptr, size_t size)
{
  if (!ptr)
    return;

  void **p = (void **) ptr;

  if (size == 0)
  {
    if (*p)
    {
      free(*p);
      *p = NULL;
    }
    return;
  }

  void *r = realloc(*p, size);
  if (!r)
  {
    mutt_error(_("Out of memory"));
    mutt_exit(1);
  }

  *p = r;
}

void mutt_mem_realloc_zero(void *ptr, size_t cur_size, size_t new_size)
{
  if (!ptr)
    return;

  mutt_mem_realloc(ptr, new_size);

  unsigned char *p = *(unsigned char **) ptr;

  if (!*p || (new_size == 0) || (new_size <= cur_size))
    return;

  memset(p + cur_size, '\0', new_size - cur_size);
}

void dump_mem(unsigned char *ptr, size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    printf("%02x ", ptr[i]);
  }
  printf("\n");
}

int main()
{
  const int step = 10;
  unsigned char *ptr = NULL;
  size_t plen = 0;

  plen += step;
  mutt_mem_realloc(&ptr, plen);
  for (size_t i = 0; i < plen; i++)
    ptr[i] = 40 + i;
  dump_mem(ptr, plen);

  mutt_mem_realloc_zero(&ptr, plen, plen + step);
  plen += step;
  dump_mem(ptr, plen);

  mutt_mem_free(&ptr);

  return 0;
}
