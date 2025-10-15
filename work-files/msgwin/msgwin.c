#define _XOPEN_SOURCE
#include "config.h"
#include <errno.h>
#include <locale.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include "mutt/lib.h"
#include "config/lib.h"
#include "gui/msgwin_wdata.h"
#include "mutt.h"
#include "browser/lib.h"
#include "color/lib.h"

int AbortKey;
bool OptForceRefresh;
bool OptIgnoreMacroEvents;
bool OptKeepQuiet;
bool OptNoCurses;
int SigInt;
int SigWinch;

void measure(struct MwCharArray *chars, const char *str, enum ColorId color);
int msgwin_calc_rows(struct MsgWinWindowData *wdata, int cols, const char *str);
void dump_rows(struct MsgWinWindowData *wdata);

// clang-format off
bool attr_color_is_set(struct AttrColor *ac) { return false; }
void dlg_browser(struct Buffer *file, SelectFileFlags flags, struct Mailbox *m, char ***files, int *numfiles) {}
struct MuttWindow *helpbar_new(void) { return NULL; }
struct AttrColor *merged_color_overlay(struct AttrColor *base, struct AttrColor *over) { return NULL; }
void mutt_clear_error(void) {}
int mutt_monitor_poll(void) { return 0; }
int mutt_system(const char *cmd) { return 0; }
int mw_get_field(const char *field, struct Buffer *buf, CompletionFlags complete, bool multiple, struct Mailbox *m, char ***files, int *numfiles) { return 0; }
int mw_yesorno(const char *msg, enum QuadOption def) { return 0; }
void nm_edata_free(void **ptr) {}
struct AttrColor *simple_color_get(enum ColorId cid) { return NULL; }
// clang-format on

#define MSGWIN_COLS 40

int log_disp_debug(time_t stamp, const char *file, int line, const char *function, enum LogLevel level, const char *format, ...)
{
  char buf[LOG_LINE_MAX_LEN] = { 0 };

  va_list ap;
  va_start(ap, format);
  int rc = vsnprintf(buf, sizeof(buf), format, ap);
  va_end(ap);

  log_disp_file(stamp, file, line, function, level, "%s", buf);

  FILE *fp = (level < LL_MESSAGE) ? stderr : stdout;
  int err = errno;
  int colour = 0;
  bool tty = (isatty(fileno(fp)) == 1);

  if (tty)
  {
    switch (level)
    {
      case LL_PERROR:
      case LL_ERROR:
        colour = 31;
        break;
      case LL_WARNING:
        colour = 33;
        break;
      case LL_MESSAGE:
      default:
        break;
    }
  }

  if (colour > 0)
    rc += fprintf(fp, "\033[1;%dm", colour); // Escape

  fputs(buf, fp);

  if (level == LL_PERROR)
    rc += fprintf(fp, ": %s", strerror(err));

  if (colour > 0)
    rc += fprintf(fp, "\033[0m"); // Escape

  // rc += fprintf(fp, "\n");

  return rc;
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  MuttLogger = log_disp_debug;

  enum ColorId cid = MT_COLOR_ATTACHMENT;
  struct MsgWinWindowData *wdata = msgwin_wdata_new();

  for (int i = 1; i < argc; i++, cid++)
  {
    const char *str = argv[i];
    size_t bytes = strlen(str);
    mutt_debug(LL_DEBUG1, "\033[7m>>\033[0m%s\033[7m<<\033[0m\n", str);
    mutt_debug(LL_DEBUG1, "%zu bytes\n", bytes);

    buf_addstr(wdata->text, str);
    measure(&wdata->chars, str, cid);
  }

  mutt_debug(LL_DEBUG1, "\n");
  mutt_debug(LL_DEBUG1, "%s\n", buf_string(wdata->text));

  int cols = MSGWIN_COLS;
  mutt_debug(LL_DEBUG1, "wrapping to %d columns\n", cols);
  int rows = msgwin_calc_rows(wdata, cols, buf_string(wdata->text));
  mutt_debug(LL_DEBUG1, "%d rows\n", rows);
  mutt_debug(LL_DEBUG1, "\n");

  dump_rows(wdata);

  msgwin_wdata_free(NULL, (void **) &wdata);
}
