#include <errno.h>
#include <ncurses.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static void failed(const char *name)
{
  printw("...%s failed", name);
  getch();
  endwin();
  exit(1);
}

static void do_pair_content(int pair)
{
  int f = 0, b = 0;

  int rc = extended_pair_content(0, &f, &b);
  if (rc != OK)
    failed("pair_content");
  printw("pair %d contains (%d,%d)\n", pair, f, b);
}

static void do_init_pair(int pair, int fg, int bg)
{
  int rc = init_extended_pair(pair, fg, bg);
  if (rc != OK)
    failed("init_pair");
}

static void do_init_color(int color, int adjust)
{
  int r = 0, g = 0, b = 0;

  int rc = extended_color_content(color, &r, &g, &b);
  if (rc != OK)
    failed("color_content");

  r = (adjust + 1000 + r) % 1000;
  g = (adjust + 1000 + g) % 1000;
  b = (adjust + 1000 + b) % 1000;

  rc = init_extended_color(color, r, g, b);
  if (rc != OK)
    failed("init_extended_color");
}

static void do_color_set(const char *expected, int pair)
{
  int rc = color_set((short) pair, (void *) &pair);
  printw("%s\n", expected);
  if (rc != OK)
    failed("color_set");
}

static void show_1_rgb(const char *name, int color, int y, int x)
{
  int r = 0, g = 0, b = 0;

  int rc = extended_color_content(color, &r, &g, &b);
  wmove(stdscr, y, x);
  if (rc == OK)
  {
    printw("%-8s %3d/%3d/%3d", name, r, g, b);
  }
  else
  {
    printw("%-8s", name);
  }
}

static void show_rgb(void)
{
  int y = 0, x = 0;
  getyx(stdscr, y, x);
  show_1_rgb("RED", COLOR_RED, y + 10, x);
  show_1_rgb("GREEN", COLOR_GREEN, y + 11, x);
  show_1_rgb("BLUE", COLOR_BLUE, y + 12, x);
  wmove(stdscr, y, x);
}

int main()
{
  initscr();
  cbreak();
  noecho();

  if (!has_colors())
  {
    endwin();
    fprintf(stderr, "This demo requires a color terminal\n");
    return 1;
  }

  start_color();
  printw("COLORS %d\n", COLORS);
  printw("COLOR_PAIRS %d\n", COLOR_PAIRS);

  do_pair_content(0);

  int r = 0, g = 0, b = 0;
  int color = 207;
  int rc = extended_color_content(color, &r, &g, &b);
  if (rc == OK)
  {
    printw("colour %d == %d, %d, %d\n", color, r, g, b);
    printw("colour %d == 0x%02x%02x%02x\n", color, r*255/1000, g*255/1000, b*255/1000);
  }

  rc = extended_color_content(color, &r, &g, &b);
  if (rc == OK)
  {
    printw("colour %d == %d, %d, %d\n", color, r, g, b);
    printw("colour %d == 0x%02x%02x%02x\n", color, r*255/1000, g*255/1000, b*255/1000);
  }

  rc = init_extended_color(207, 1000, 0, 0);
  if (rc != OK)
    failed("init_color");

  rc = extended_color_content(color, &r, &g, &b);
  if (rc == OK)
  {
    printw("colour %d == %d, %d, %d\n", color, r, g, b);
    printw("colour %d == 0x%02x%02x%02x\n", color, r*255/1000, g*255/1000, b*255/1000);
  }

  printw("Initializing pair 1 to red/black\n");
  do_init_pair(1, COLOR_RED, 207);
  do_color_set("RED/BLACK", 1);

  rc = extended_color_content(color, &r, &g, &b);
  if (rc == OK)
  {
    printw("colour %d == %d, %d, %d\n", color, r, g, b);
    printw("colour %d == 0x%02x%02x%02x\n", color, r*255/1000, g*255/1000, b*255/1000);
  }

  printw("Initializing pair 2 to white/blue\n");
  do_init_pair(2, COLOR_WHITE, COLOR_BLUE);
  do_color_set("WHITE/BLUE", 2);

  printw("Initializing pair 3 to green/black\n");
  do_init_pair(3, COLOR_GREEN, COLOR_BLACK);
  do_color_set("GREEN/BLACK", 3);

  printw("Resetting colors to pair 0\n");
  do_color_set("Default Colors", 0);

  printw("Resetting colors to pair 1\n");
  do_color_set("RED/BLACK", 1);

  if (can_change_color())
  {
    do_color_set("Default Colors", 0);
    printw("Press any key to stop...\n");
    getch();
    nodelay(stdscr, true);
    while (getch() == ERR)
    {
      show_rgb();
      do_init_color(COLOR_RED, 1);
      do_init_color(COLOR_BLUE, -1);
      do_init_color(207, 1);
      napms(5);
    }
    nodelay(stdscr, false);
  }

  rc = extended_color_content(color, &r, &g, &b);
  if (rc == OK)
  {
    printw("colour %d == %d, %d, %d\n", color, r, g, b);
    printw("colour %d == 0x%02x%02x%02x\n", color, r*255/1000, g*255/1000, b*255/1000);
  }
  getch();

  endwin();

  return 0;
}
