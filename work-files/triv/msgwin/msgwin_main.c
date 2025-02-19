#include <wchar.h>

  if (batch_mode)
  {
    size_t wbuflen = 16;
    wchar_t *wbuf = calloc(wbuflen, sizeof(wchar_t));
    const char *str = "♥️🍏한";
    printf("%s\n", str);
    mutt_mb_mbstowcs(&wbuf, &wbuflen, 0, str);
    unsigned char *buf = (unsigned char *) wbuf;
    for (int j = 0; j < (16 * sizeof(wchar_t)); j++)
    {
      printf("%02x ", buf[j]);
      if (wbuf[(j-3)/4] == 0)
        break;
    }
    printf("\n");
    for (int j = 0; j < 16; j++)
    {
      printf("%-11d ", wcwidth(wbuf[j]));
      if (wbuf[j] == 0)
        break;
    }
    printf("\n");
    free(wbuf);

