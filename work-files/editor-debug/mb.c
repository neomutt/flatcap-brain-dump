#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define ICONV_ILLEGAL_SEQ ((size_t) -1)
#define ICONV_BUF_TOO_SMALL ((size_t) -2)

wchar_t ReplacementChar = '?';

size_t mutt_mb_mbstowcs(wchar_t **pwbuf, size_t *pwbuflen, size_t i, const char *buf)
{
  if (!pwbuf || !pwbuflen || !buf)
    return 0;

  wchar_t wc = 0;
  mbstate_t mbstate = { 0 };
  size_t k;
  wchar_t *wbuf = *pwbuf;
  size_t wbuflen = *pwbuflen;

  while (*buf != '\0')
  {
    memset(&mbstate, 0, sizeof(mbstate));
    for (; (k = mbrtowc(&wc, buf, MB_LEN_MAX, &mbstate)) && (k != ICONV_ILLEGAL_SEQ) && (k != ICONV_BUF_TOO_SMALL); buf += k)
    {
      if (i >= wbuflen)
      {
        wbuflen = i + 20;
        wbuf = realloc(&wbuf, wbuflen * sizeof(*wbuf));
      }
      wbuf[i++] = wc;
    }
    if ((*buf != '\0') && ((k == ICONV_ILLEGAL_SEQ) || (k == ICONV_BUF_TOO_SMALL)))
    {
      if (i >= wbuflen)
      {
        wbuflen = i + 20;
        wbuf = realloc(&wbuf, wbuflen * sizeof(*wbuf));
      }
      wbuf[i++] = ReplacementChar;
      buf++;
    }
  }

  *pwbuf = wbuf;
  *pwbuflen = wbuflen;
  return i;
}

// int main(int argc, char *argv[])
int main()
{
  char *loc = NULL;

  loc = setlocale(LC_ALL, "");
  printf("empty: %s\n", loc);

  loc = setlocale(LC_ALL, "C.UTF-8");
  printf("c: %s\n", loc);

  loc = setlocale(LC_ALL, "en_US.UTF-8");
  printf("us: %s\n", loc);

  printf("LC_ALL   = %s\n", getenv("LC_ALL"));
  printf("LANG     = %s\n", getenv("LANG"));
  printf("LC_CTYPE = %s\n", getenv("LC_CTYPE"));
  printf("\n");

  size_t wbuf_len = 64;
  wchar_t *wbuf = calloc(1, wbuf_len);
  const char *src = "义勇军";

  printf("src = %s\n", src);
  size_t num = strlen(src);

  const unsigned char *usrc = (const unsigned char *) src;
  printf("0x");
  for (size_t i = 0; i < num; i++)
  {
    printf("%04x ", usrc[i]);
  }
  printf("\n");

  num = mutt_mb_mbstowcs(&wbuf, &wbuf_len, 0, src);

  printf("\n");
  printf("num = %zu\n", num);

  printf("result\n");
  printf("0x");
  for (size_t i = 0; i < num; i++)
  {
    printf("%04x ", wbuf[i]);
  }
  printf("\n");

  return 0;
}
