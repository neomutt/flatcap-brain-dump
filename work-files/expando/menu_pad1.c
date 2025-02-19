static void menu_pad_string(struct Menu *menu, struct Buffer *buf)
{
  char *scratch = buf_strdup(buf);
  const bool c_arrow_cursor = cs_subset_bool(menu->sub, "arrow_cursor");
  const char *const c_arrow_string = cs_subset_string(menu->sub, "arrow_string");
  const int shift = c_arrow_cursor ? mutt_strwidth(c_arrow_string) + 1 : 0;
  const int cols = menu->win->state.cols - shift;

  mutt_simple_format(buf->data, buf->dsize, cols, cols, JUSTIFY_LEFT, ' ', scratch, mutt_str_len(scratch), true);
  FREE(&scratch);
}
