#include <stdio.h>
#include <string.h>

/**
 * enum AnsiSeqType - XXX
 */
enum AnsiSeqType
{
  AST_NONE,  ///< XXX
  AST_COLOR, ///< XXX
  AST_OTHER  ///< XXX
};

/**
 * ansi_measure_csi - XXX
 */
int ansi_measure_csi(const char *src, char *end)
{
  static const char *parameter = "0123456789:;<=>?";
  static const char *intermediate = " !\"#$%&'()*+,-./";
  static const char *final = "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

  if (!src || (src[0] != '\033') || (src[1] != '['))
    return 0;

  src += 2; // Skip <esc>[
  int total = 0;
  int len;

  // Count parameter bytes
  len = strspn(src, parameter);
  printf("Found %d parameter bytes\n", len);
  printf(">>%.*s<<\n", (int) len, src);
  total += len;
  src += len;

  // Count intermediate bytes
  len = strspn(src, intermediate);
  printf("Found %d intermediate bytes\n", len);
  printf(">>%.*s<<\n", (int) len, src);
  total += len;
  src += len;

  // Check for a valid final byte
  char *final_char = strchr(final, src[0]);
  if (final_char) // A valid ANSI sequence
  {
    *end = src[0];
    printf("Valid ANSI sequence\n");
    if (src[0] == 'm') // ANSI Colour sequence
    {
      printf("ANSI colour sequence\n");
      total++;
    }
  }

  printf("Total length = %d\n", total);
  return total;
}

/**
 * ansi_measure_osc - XXX
 */
int ansi_measure_osc(const char *src)
{
  // Ctrl-A, Ctrl-G (Bel), Escape
  static const char *final = "\001\007\033";

  if (!src || (src[0] != '\033') || (src[1] != ']'))
    return 0;

  src += 2; // Skip <esc>]

  printf("searching >>%s<<\n", src);
  int len = strcspn(src, final);
  if (len > 0)
  {
    printf("len = %d\n", len);
    printf("final = %d\n", src[len]);
  }

  return 0;
}

/**
 * ansi_measure - XXX
 */
int ansi_measure(const char *src, enum AnsiSeqType *type)
{
  if (!src || !type)
    return 0;

  *type = AST_NONE;

  if (src[0] != '\033')
    return 0;

  int len;
  if (src[1] == '[')
  {
    char end = '\0';
    len = ansi_measure_csi(src, &end);
    if (len > 0)
      *type = AST_COLOR;
  }

  if (src[1] == ']')
  {
    len = ansi_measure_osc(src);
    if (len > 0)
      *type = AST_OTHER;
  }

  return len;
}

/**
 * main - XXX
 */
int main(int argc, char *argv[])
{
  for (int i = 1; i < argc; i++)
  {
    enum AnsiSeqType type = AST_NONE;
    int len = ansi_measure(argv[i], &type);
    printf("%d (%d)\n", len, type);
  }
  return 0;
}
