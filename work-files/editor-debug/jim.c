#include "config.h"
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "mutt/lib.h"
#include "core/lib.h"
#include "enter/lib.h"

// #define LOCALES_HACK 1
// #undef IsWPrint

#ifdef LOCALES_HACK
#define IsWPrint(wc) (iswprint(wc) || (wc >= 0xa0))
#else
#define IsWPrint(wc) (iswprint(wc) || (OptLocales ? 0 : (wc >= 0xa0)))
#endif

#define COMB_CHAR(wc) (IsWPrint(wc) && (wcwidth(wc) == 0))

int editor_backspace(struct EnterState *es)
{
  if (!es || (es->curpos == 0))
    return FR_ERROR;

  size_t i = es->curpos;
  while ((i > 0) && COMB_CHAR(es->wbuf[i - 1]))
    i--;
  if (i > 0)
    i--;
  memmove(es->wbuf + i, es->wbuf + es->curpos,
          (es->lastchar - es->curpos) * sizeof(wchar_t));
  es->lastchar -= es->curpos - i;
  es->curpos = i;

  return FR_SUCCESS;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  setlocale(LC_ALL, "");
  OptLocales = true;

  // struct EnterState *es = enter_state_new();

  size_t wide_len = 128;
  wchar_t *wide = calloc(1, wide_len);
  size_t num = mutt_mb_mbstowcs(&wide, &wide_len, 0, argv[1]);

  printf("%s\n", argv[1]);
  printf("%zu chars\n\n", num);

  unsigned char *ptr = argv[1];
  for (size_t i = 0; ptr[i]; i++)
  {
    printf("%02x ", ptr[i]);
  }
  printf("\n\n");

  ptr = (unsigned char *) wide;
  for (size_t i = 0; i < (num * 4); i++)
  {
    printf("%02x ", ptr[i]);
    if ((i % 4) == 3)
      printf(" ");
  }
  printf("\n");

  for (size_t i = 0; i < num; i++)
  {
    printf("%c %c %2d       ", iswprint(wide[i]) ? 'P' : '.', COMB_CHAR(wide[i]) ? 'C' : '.', wcwidth(wide[i]));
  }
  printf("\n");

  // enter_state_free(&es);
  free(wide);
  return 0;
}
