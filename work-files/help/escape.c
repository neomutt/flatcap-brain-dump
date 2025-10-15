/**
 * escape_macro - Escape any special characters in a macro
 * @param[in]  macro Macro string
 * @param[out] buf   Buffer for the result
 */
static void escape_macro(const char *macro, struct Buffer *buf)
{
  wchar_t wc = 0;
  size_t k;
  size_t len = mutt_str_len(macro);
  mbstate_t mbstate1 = { 0 };
  mbstate_t mbstate2 = { 0 };

  for (; (len > 0) && (k = mbrtowc(&wc, macro, MB_LEN_MAX, &mbstate1)); macro += k, len -= k)
  {
    if ((k == ICONV_ILLEGAL_SEQ) || (k == ICONV_BUF_TOO_SMALL))
    {
      if (k == ICONV_ILLEGAL_SEQ)
        memset(&mbstate1, 0, sizeof(mbstate1));
      k = (k == ICONV_ILLEGAL_SEQ) ? 1 : len;
      wc = ReplacementChar;
    }

    const int w = wcwidth(wc);
    if (IsWPrint(wc) && (w >= 0))
    {
      char tmp[MB_LEN_MAX * 2] = { 0 };
      if (wcrtomb(tmp, wc, &mbstate2) != ICONV_ILLEGAL_SEQ)
      {
        buf_addstr(buf, tmp);
      }
    }
    else if ((wc < 0x20) || (wc == 0x7f))
    {
      if (wc == '\033') // Escape
        buf_addstr(buf, "\\e");
      else if (wc == '\n')
        buf_addstr(buf, "\\n");
      else if (wc == '\r')
        buf_addstr(buf, "\\r");
      else if (wc == '\t')
        buf_addstr(buf, "\\t");
      else
        buf_add_printf(buf, "^%c", (char) ((wc + '@') & 0x7f));
    }
    else
    {
      buf_addch(buf, '?');
    }
  }
}

