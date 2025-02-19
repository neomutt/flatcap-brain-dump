static void menu_pad_string(struct Menu *menu, struct Buffer *buf)
{
  buf_fix_dptr(buf);

  int target = menu->win->state.cols; // Target width in screen cells

  const bool c_arrow_cursor = cs_subset_bool(menu->sub, "arrow_cursor");
  if (c_arrow_cursor)
  {
    // Save some space for the arrow cursor
    const char *const c_arrow_string = cs_subset_string(menu->sub, "arrow_string");
    const int arrow = mutt_strwidth(c_arrow_string) + 1;
    if (target >= arrow)
      target -= arrow;
  }

  const int string = mutt_strwidth(buf_string(buf)); // Width of the current string
  if (string == target)
    return;

  if (string > target) // Too long, truncate
  {
    size_t bytes = mutt_wstr_trunc(buf_string(buf), buf->dsize, target, NULL);
    buf->data[bytes] = '\0';
    return;
  }

  // Pad the string with spaces
  buf_add_printf(buf, "%*s", (target - string), "");
}
