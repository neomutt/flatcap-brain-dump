#include <stdio.h>

int main()
{

  printf("|%d|\n", -42);                     // |42|                |-42|
  printf("|%0d|\n", -42);                    // |42|                |-42|
  printf("|%5d|\n", -42);                    // |   42|             |  -42|
  printf("|%05d|\n", -42);                   // |00042|             |-0042|
  printf("|%-5d|\n", -42);                   // |42   |             |-42  |

  // printf("|%.-2d|\n", -42);
  // printf("|%0.-2d|\n", -42);
  // printf("|%5.-2d|\n", -42);
  // printf("|%05.-2d|\n", -42);
  // printf("|%-5.-2d|\n", -42);

  printf("|%.8d|\n", -42);                   // |00000042|          |-00000042|
  printf("|%5.8d|\n", -42);                  // |00000042|          |-00000042|
  printf("|%-5.8d|\n", -42);                 // |00000042|          |-00000042|

  printf("|%.d|\n", -42);                    // |42|                |-42|
  printf("|%-d|\n", -42);                    // |42|                |-42|
  printf("|%-.8d|\n", -42);                  // |00000042|          |-00000042|
  printf("|%-.d|\n", -42);                   // |42|                |-42|
  printf("|%5.d|\n", -42);                   // |   42|             |  -42|
  printf("|%-5.d|\n", -42);                  // |42   |             |-42  |
  printf("|%-0d|\n", -42);                   // |42|                |-42|

  printf("|%08d|\n", 42);                    // |00000042|          |-0000042|
  printf("|%8d|\n", 42);                     // |      42|          |     -42|
  printf("|%-08d|\n", 42);                   // |42      |          |-42     |
  printf("|%-8d|\n", 42);                    // |42      |          |-42     |

  printf("|%05.0d|\n", 0);                   // |     |
  // '0' flag ignored with precision and ‘%d’
  printf("|%0.0d|\n", 0);                    // ||
  // '0' flag ignored with precision and ‘%d’
  printf("|%5.0d|\n", 0);                    // |     |
  printf("|%.0d|\n", 0);                     // ||
  printf("|%-05.0d|\n", 0);                  // |     |
  // '0' flag ignored with '-' flag
  // '0' flag ignored with precision and ‘%d’
  printf("|%-0.0d|\n", 0);                   // ||
  // '0' flag ignored with '-' flag
  // '0' flag ignored with precision and ‘%d’
  printf("|%-5.0d|\n", 0);                   // |     |
  printf("|%-.0d|\n", 0);                    // ||

  // '0' flag ignored with '-' flag
  printf("|%-05d|\n", -42);                  // |42   |             |-42  |
  // '0' flag ignored with '-' flag
  printf("|%0.8d|\n", -42);                  // |00000042|          |-00000042|
  // '0' flag ignored with precision and ‘%d’
  printf("|%05.8d|\n", -42);                 // |00000042|          |-00000042|
  // '0' flag ignored with precision and ‘%d’
  printf("|%-0.8d|\n", -42);                 // |00000042|          |-00000042|
  // '0' flag ignored with '-' flag
  // '0' flag ignored with precision and ‘%d’
  printf("|%-05.8d|\n", -42);                // |00000042|          |-00000042|
  // '0' flag ignored with '-' flag
  // '0' flag ignored with precision and ‘%d’
  printf("|%05.d|\n", -42);                  // |   42|             |  -42|
  // '0' flag ignored with precision and ‘%d’
  printf("|%0.d|\n", -42);                   // |42|                |-42|
  // '0' flag ignored with precision and ‘%d’
  printf("|%-05.d|\n", -42);                 // |42   |             |-42  |
  // '0' flag ignored with '-' flag
  // '0' flag ignored with precision and ‘%d’
  printf("|%-0.d|\n", -42);                  // |42|                |-42|
  // '0' flag ignored with '-' flag
  // '0' flag ignored with precision and ‘%d’
  printf("|%-08d|\n", 42);                   // |42      |          |-42     |
  // '0' flag ignored with '-' flag

  printf("|%0s|\n", "hello");                // |hello|
  // '0' flag used with ‘%s’ format
  printf("|%4s|\n", "hello");                // |hello|
  printf("|%04s|\n", "hello");               // |hello|
  // '0' flag used with ‘%s’ format
  printf("|%14s|\n", "hello");               // |         hello|
  printf("|%.0s|\n", "hello");               // ||
  printf("|%.4s|\n", "hello");               // |hell|
  printf("|%.14s|\n", "hello");              // |hello|
  printf("|%20.0s|\n", "hello");             // |                    |
  printf("|%20.4s|\n", "hello");             // |                hell|
  printf("|%20.14s|\n", "hello");            // |               hello|

  return 0;
}
