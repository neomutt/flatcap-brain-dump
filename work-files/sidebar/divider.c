/**
 * set_divider - Update the divider data and decide what actions are required
 * @param wdata   Sidebar data
 * @param ascii   true, if `$ascii_chars` is set
 * @param div_str Divider string, `$sidebar_divider_char`
 * @retval num Action required, e.g. #WA_REPAINT
 *
 * If the divider changes width, then Window will need to be reflowed.
 */
static WindowActionFlags set_divider(struct SidebarWindowData *wdata, bool ascii, const char *div_str)
{
  enum DivType type = SB_DIV_USER;

  // Calculate the width of the delimiter in screen cells
  int width = mutt_strwidth(C_SidebarDividerChar);
  if (width < 1) // Bad character or empty
  {
    type = ascii ? SB_DIV_ASCII : SB_DIV_UTF8;
    width = 1;
  }
  else if (ascii)
  {
    for (int i = 0; i < width; i++)
    {
      if (div_str[i] & ~0x7F) // high-bit is set
      {
        type = SB_DIV_ASCII;
        width = 1;
        break;
      }
    }
  }

  WindowActionFlags action = WA_REPAINT;
  if (width != wdata->divider_width)
    action = WA_REFLOW;

  wdata->divider_width = width;
  wdata->divider_type = type;
  mutt_str_replace(&wdata->divider_str, div_str);

  return action;
}
