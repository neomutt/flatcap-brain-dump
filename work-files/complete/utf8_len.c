#include <stdio.h>

#define INVALID (-2)

int fgetutf8c(FILE *f)
{
  int result = 0;
  int input[6] = { 0 };

  input[0] = fgetc(f);
  printf("(i[0] = %d) ", input[0]);
  if (input[0] == EOF)
  {
    // The EOF was hit by the first character.
    result = EOF;
  }
  else if (input[0] < 0x80)
  {
    // the first character is the only 7 bit sequence...
    result = input[0];
  }
  else if ((input[0] & 0xC0) == 0x80)
  {
    // This is not the beginning of the multibyte sequence.
    return INVALID;
  }
  else if ((input[0] & 0xfe) == 0xfe)
  {
    // This is not a valid UTF-8 stream.
    return INVALID;
  }
  else
  {
    int sequence_length;
    for (sequence_length = 1; input[0] & (0x80 >> sequence_length); ++sequence_length)
      ;
    result = input[0] & ((1 << sequence_length) - 1);
    printf("sequence length = %d ", sequence_length);
    int index;
    for (index = 1; index < sequence_length; ++index)
    {
      input[index] = fgetc(f);
      printf("(i[%d] = %d) ", index, input[index]);
      if (input[index] == EOF)
      {
        return EOF;
      }
      result = (result << 6) | (input[index] & 0x30);
    }
  }
  return result;
}

int main(int argc, char **argv)
{
  if (argc != 2)
    return 1;

  printf("open(%s) ", argv[1]);
  FILE *f = fopen(argv[1], "r");
  int c = 0;
  while (c != EOF)
  {
    c = fgetutf8c(f);
    printf("* %d\n", c);
  }
  fclose(f);
  return 0;
}
