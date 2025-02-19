#include "config.h"
#include <assert.h>
#include <locale.h>
#include <stdio.h>
#include "mutt/lib.h"
#include "core/lib.h"
#include "enter/lib.h"

#define TEST_CHECK assert

struct NeoMutt *NeoMutt = NULL;

void dump(void *ptr, int num)
{
  unsigned char *str = (unsigned char *) ptr;
  for (int i = 0; i < num; i++)
  {
    printf("%02x ", str[i]);
    if (((i + 1) % 4) == 0)
      printf("| ");
  }
  printf("\n");
}

int main()
{
  setlocale(LC_ALL, "en_US.UTF-8");

  {
    char buf[64];
    const char *str =
      "I ❤️xyz";
      // "test";
      // "义勇军";
    struct EnterState *es = mutt_enter_state_new();
    editor_buffer_set(es, str);
    // printf("[[%ls]]\n", es->wbuf);
    dump(es->wbuf, 32);
    mutt_mb_wcstombs(buf, sizeof(buf), es->wbuf, es->lastchar);
    printf(">>%s<<\n", buf);
    TEST_CHECK(editor_buffer_get_lastchar(es) == 7);
    TEST_CHECK(editor_buffer_get_cursor(es) == 7);
    editor_buffer_set_cursor(es, 2);
    TEST_CHECK(editor_buffer_get_cursor(es) == 2);
    TEST_CHECK(editor_delete_char(es) == FR_SUCCESS);
    TEST_CHECK(editor_buffer_get_lastchar(es) == 5);
    TEST_CHECK(editor_buffer_get_cursor(es) == 2);
    dump(es->wbuf, 32);
    mutt_mb_wcstombs(buf, sizeof(buf), es->wbuf, es->lastchar);
    printf(">>%s<<\n", buf);
    mutt_enter_state_free(&es);
  }

#if 0
  {
    const char *str =
      // "I ❤️";
      // "test";
      "义勇军";
    printf(">>%s<< (%ld)\n", str, strlen(str));
    struct EnterState *es = mutt_enter_state_new();
    editor_buffer_set(es, str);

    // printf("%ld\n", sizeof(es->wbuf[0]));
    dump(es->wbuf, 32);

    printf("%ld\n", editor_buffer_get_cursor(es));
    // TEST_CHECK(editor_buffer_get_cursor(es) == 8);
    TEST_CHECK(editor_backspace(es) == FR_SUCCESS);
    printf("%ld\n", editor_buffer_get_cursor(es));
    // TEST_CHECK(editor_buffer_get_cursor(es) == 1);
    mutt_enter_state_free(&es);
  }

  {
    struct EnterState *es = mutt_enter_state_new();
    editor_buffer_set(es, "I ❤️✉️  ️xyz");
    printf("0>>%lc<<\n", es->wbuf[0]);
    printf("1>>%lc<<\n", es->wbuf[1]);
    printf("2>>%lc<<\n", es->wbuf[2]);
    printf("3>>%lc<<\n", es->wbuf[3]);
    printf("4>>%lc<<\n", es->wbuf[4]);
    printf("5>>%lc<<\n", es->wbuf[5]);
    printf("6>>%lc<<\n", es->wbuf[6]);
    printf("%ld\n", editor_buffer_get_lastchar(es));
    printf("%ld\n", editor_buffer_get_cursor(es));
    TEST_CHECK(editor_buffer_get_lastchar(es) == 12);
    TEST_CHECK(editor_buffer_get_cursor(es) == 12);
    editor_buffer_set_cursor(es, 4);
    TEST_CHECK(editor_buffer_get_cursor(es) == 4);
    printf("[[%ls]]\n", es->wbuf);
    TEST_CHECK(editor_transpose_chars(es) == FR_SUCCESS);
    printf("[[%ls]]\n", es->wbuf);
    TEST_CHECK(editor_buffer_get_lastchar(es) == 12);
    TEST_CHECK(editor_buffer_get_cursor(es) == 5);
    mutt_enter_state_free(&es);
  }
#endif
  return 0;
}
