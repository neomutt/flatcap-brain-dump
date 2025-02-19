int mutt_buffer_get_field(const char *field, struct Buffer *buf, CompletionFlags complete,
                          bool multiple, struct Mailbox *m, char ***files, int *numfiles)
{
  struct MuttWindow *win = msgwin_get_window();
  if (!win)
    return -1;

  int rc;
  int col;

  struct EnterState *es = mutt_enter_state_new();

  const struct Mapping *old_help = win->help_data;
  int old_menu = win->help_menu;

  win->help_data = EditorHelp;
  win->help_menu = MENU_EDITOR;
  struct MuttWindow *old_focus = window_set_focus(win);

  enum MuttCursorState cursor = mutt_curses_set_cursor(MUTT_CURSOR_VISIBLE);
  window_redraw(win);
  do
  {
    if (SigWinch)
    {
      SigWinch = false;
      mutt_resize_screen();
      clearok(stdscr, true);
      window_redraw(NULL);
    }
    mutt_window_clearline(win, 0);
    mutt_curses_set_normal_backed_color_by_id(MT_COLOR_PROMPT);
    mutt_window_addstr(win, field);
    mutt_curses_set_color_by_id(MT_COLOR_NORMAL);
    mutt_refresh();
    mutt_window_get_coords(win, &col, NULL);
    rc = mutt_enter_string_full(buf->data, buf->dsize, col, complete, multiple,
                                m, files, numfiles, es);
  } while (rc == 1);
  mutt_curses_set_cursor(cursor);

  win->help_data = old_help;
  win->help_menu = old_menu;
  mutt_window_move(win, 0, 0);
  mutt_window_clearline(win, 0);
  window_set_focus(old_focus);

  if (rc == 0)
    mutt_buffer_fix_dptr(buf);
  else
    mutt_buffer_reset(buf);

  mutt_enter_state_free(&es);

  return rc;
}


int mutt_get_field_unbuffered(const char *msg, struct Buffer *buf, CompletionFlags flags)
{
  bool reset_ignoremacro = false;

  if (!OptIgnoreMacroEvents)
  {
    OptIgnoreMacroEvents = true;
    reset_ignoremacro = true;
  }
  int rc = mutt_buffer_get_field(msg, buf, flags, false, NULL, NULL, NULL);
  if (reset_ignoremacro)
    OptIgnoreMacroEvents = false;

  return rc;
}

