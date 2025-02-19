#include <stdbool.h>
#include <stdio.h>

// clang-format off
// Tree chars (UTF-8) -- Each padded to 4 chars with NULs
static const char *tree_utf8 =
  "\342\224\224\0"   //  └  U+2514 - Box Drawings Light Up and Right
  "\342\224\214\0"   //  ┌  U+250C - Box Drawings Light Down and Right
  "\342\224\234\0"   //  ├  U+251C - Box Drawings Light Vertical and Right
  "\342\224\200\0"   //  ─  U+2500 - Box Drawings Light Horizontal
  "\342\224\202\0"   //  │  U+2502 - Box Drawings Light Vertical
  "\342\224\254\0"   //  ┬  U+252C - Box Drawings Light Down and Horizontal
  "\342\224\264\0"   //  ┴  U+2534 - Box Drawings Light Up and Horizontal
  " \0\0\0"          //     U+0020 - Space
  ">\0\0\0"          //  >  U+003E - Greater-Than Sign
  "*\0\0\0"          //  *  U+002A - Asterisk
  "&\0\0\0"          //  &  U+0026 - Ampersand
  "=\0\0\0"          //  =  U+003D - Equals Sign
  "?\0\0\0";         //  ?  U+003F - Question Mark

// Tree chars (ASCII) -- Each padded to 4 chars with NULs
static const char *tree_ascii =
  "`\0\0\0"          //  `  U+0060 - Grave Accent
  ",\0\0\0"          //  ,  U+002C - Comma
  "|\0\0\0"          //  |  U+007C - Vertical Line
  "-\0\0\0"          //  -  U+002D - Hyphen-Minus
  "|\0\0\0"          //  |  U+007C - Vertical Line
  "-\0\0\0"          //  -  U+002D - Hyphen-Minus
  "-\0\0\0"          //  -  U+002D - Hyphen-Minus
  " \0\0\0"          //     U+0020 - Space
  ">\0\0\0"          //  >  U+003E - Greater-Than Sign
  "*\0\0\0"          //  *  U+002A - Asterisk
  "&\0\0\0"          //  &  U+0026 - Ampersand
  "=\0\0\0"          //  =  U+003D - Equals Sign
  "?\0\0\0";         //  ?  U+003F - Question Mark
// clang-format off

const char *get(bool utf8, int num)
{
  num *= 4;
  if (utf8)
    return tree_utf8 + num;

  return tree_ascii + num;
}

int main()
{
  for (int i = 0; i < 13; i++)
  {
    const char *tree = get(true, i);
    printf("%X %X %X %X\n", (unsigned char) tree[0], (unsigned char) tree[1],
           (unsigned char) tree[2], (unsigned char) tree[3]);
    printf("%s\n", tree);
    tree = get(false, i);
    printf("%X %X %X %X\n", (unsigned char) tree[0], (unsigned char) tree[1],
           (unsigned char) tree[2], (unsigned char) tree[3]);
    printf("%s\n", tree);
  }
  return 0;
}
