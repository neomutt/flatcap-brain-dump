#include "config.h"
#include <stdio.h>
#include "expando/lib.h"
#include "debug/lib.h"

void nm_edata_free(void **ptr)
{
}

size_t mutt_strnwidth(const char *s, size_t n)
{
  if (!s)
  {
  }
  return n;
}

static const struct ExpandoDefinition TestFormatDef[] = {
  // clang-format off
  { "*", "padding-soft", ED_GLOBAL, ED_GLO_PADDING_SOFT, E_TYPE_STRING, node_padding_parse },
  { ">", "padding-hard", ED_GLOBAL, ED_GLO_PADDING_HARD, E_TYPE_STRING, node_padding_parse },
  { "|", "padding-eol",  ED_GLOBAL, ED_GLO_PADDING_EOL,  E_TYPE_STRING, node_padding_parse },
  { "a", "",             ED_GLOBAL,  101,         E_TYPE_STRING, NULL },
  { "b", "",             ED_GLOBAL,  102,         E_TYPE_STRING, NULL },
  { "c", "",             ED_GLOBAL,  103,         E_TYPE_STRING, NULL },
  { "d", "",             ED_GLOBAL,  104,         E_TYPE_STRING, NULL },
  { "e", "",             ED_GLOBAL,  105,         E_TYPE_STRING, NULL },
  { "f", "",             ED_GLOBAL,  106,         E_TYPE_STRING, NULL },
  { "g", "",             ED_GLOBAL,  107,         E_TYPE_STRING, NULL },
  { "h", "",             ED_GLOBAL,  108,         E_TYPE_STRING, NULL },
  { "i", "",             ED_GLOBAL,  109,         E_TYPE_STRING, NULL },
  { "j", "",             ED_GLOBAL,  110,         E_TYPE_STRING, NULL },
  { "k", "",             ED_GLOBAL,  111,         E_TYPE_STRING, NULL },
  { "l", "",             ED_GLOBAL,  112,         E_TYPE_STRING, NULL },
  { "m", "",             ED_GLOBAL,  113,         E_TYPE_STRING, NULL },
  { "n", "",             ED_GLOBAL,  114,         E_TYPE_STRING, NULL },
  { "o", "",             ED_GLOBAL,  115,         E_TYPE_STRING, NULL },
  { "p", "",             ED_GLOBAL,  116,         E_TYPE_STRING, NULL },
  { "q", "",             ED_GLOBAL,  117,         E_TYPE_STRING, NULL },
  { "r", "",             ED_GLOBAL,  118,         E_TYPE_STRING, NULL },
  { "s", "",             ED_GLOBAL,  119,         E_TYPE_STRING, NULL },
  { "t", "",             ED_GLOBAL,  120,         E_TYPE_STRING, NULL },
  { "u", "",             ED_GLOBAL,  121,         E_TYPE_STRING, NULL },
  { "v", "",             ED_GLOBAL,  122,         E_TYPE_STRING, NULL },
  { "w", "",             ED_GLOBAL,  123,         E_TYPE_STRING, NULL },
  { "x", "",             ED_GLOBAL,  124,         E_TYPE_STRING, NULL },
  { "y", "",             ED_GLOBAL,  125,         E_TYPE_STRING, NULL },
  { "z", "",             ED_GLOBAL,  126,         E_TYPE_STRING, NULL },
  { "A", "",             ED_GLOBAL,  201,         E_TYPE_STRING, NULL },
  { "B", "",             ED_GLOBAL,  202,         E_TYPE_STRING, NULL },
  { "C", "",             ED_GLOBAL,  203,         E_TYPE_STRING, NULL },
  { "D", "",             ED_GLOBAL,  204,         E_TYPE_STRING, NULL },
  { "E", "",             ED_GLOBAL,  205,         E_TYPE_STRING, NULL },
  { "F", "",             ED_GLOBAL,  206,         E_TYPE_STRING, NULL },
  { "G", "",             ED_GLOBAL,  207,         E_TYPE_STRING, NULL },
  { "H", "",             ED_GLOBAL,  208,         E_TYPE_STRING, NULL },
  { "I", "",             ED_GLOBAL,  209,         E_TYPE_STRING, NULL },
  { "J", "",             ED_GLOBAL,  210,         E_TYPE_STRING, NULL },
  { "K", "",             ED_GLOBAL,  211,         E_TYPE_STRING, NULL },
  { "L", "",             ED_GLOBAL,  212,         E_TYPE_STRING, NULL },
  { "M", "",             ED_GLOBAL,  213,         E_TYPE_STRING, NULL },
  { "N", "",             ED_GLOBAL,  214,         E_TYPE_STRING, NULL },
  { "O", "",             ED_GLOBAL,  215,         E_TYPE_STRING, NULL },
  { "P", "",             ED_GLOBAL,  216,         E_TYPE_STRING, NULL },
  { "Q", "",             ED_GLOBAL,  217,         E_TYPE_STRING, NULL },
  { "R", "",             ED_GLOBAL,  218,         E_TYPE_STRING, NULL },
  { "S", "",             ED_GLOBAL,  219,         E_TYPE_STRING, NULL },
  { "T", "",             ED_GLOBAL,  220,         E_TYPE_STRING, NULL },
  { "U", "",             ED_GLOBAL,  221,         E_TYPE_STRING, NULL },
  { "V", "",             ED_GLOBAL,  222,         E_TYPE_STRING, NULL },
  { "W", "",             ED_GLOBAL,  223,         E_TYPE_STRING, NULL },
  { "X", "",             ED_GLOBAL,  224,         E_TYPE_STRING, NULL },
  { "Y", "",             ED_GLOBAL,  225,         E_TYPE_STRING, NULL },
  { "Z", "",             ED_GLOBAL,  226,         E_TYPE_STRING, NULL },
  { NULL, NULL, 0, -1, -1, NULL }
  // clang-format on
};

int main(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    struct Expando *exp = NULL;

    exp = expando_parse(argv[i], TestFormatDef, NULL);
    if (exp)
    {
      dump_graphviz_expando_node(exp->node);
      expando_free(&exp);
    }
    else
    {
      fprintf(stderr, "FAILED: %s\n", argv[i]);
    }

  }

  return 0;
}
