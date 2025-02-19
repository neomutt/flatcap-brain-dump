extern int NumCursesColors;

extern struct RegexColorList AttachList;
extern struct RegexColorList BodyList;
extern struct RegexColorList HeaderList;
extern struct RegexColorList IndexAuthorList;
extern struct RegexColorList IndexCollapsedList;
extern struct RegexColorList IndexDateList;
extern struct RegexColorList IndexFlagsList;
extern struct RegexColorList IndexLabelList;
extern struct RegexColorList IndexList;
extern struct RegexColorList IndexNumberList;
extern struct RegexColorList IndexSizeList;
extern struct RegexColorList IndexSubjectList;
extern struct RegexColorList IndexTagList;
extern struct RegexColorList IndexTagsList;
extern struct RegexColorList StatusList;

/**
 * curses_color_dump - Log one Curses colour
 * @param cc     CursesColor to log
 * @param prefix Prefix for the log line
 */
void curses_color_dump(struct CursesColor *cc, const char *prefix)
{
  if (!cc)
    return;

  char fg[16] = "-";
  char bg[16] = "-";

  if (cc->fg != -1)
    snprintf(fg, sizeof(fg), "#%06x", cc->fg);
  if (cc->bg != -1)
    snprintf(bg, sizeof(bg), "#%06x", cc->bg);

  const char *color = color_debug_log_color(cc->fg, cc->bg);
  color_debug(LL_DEBUG5, "%s| %5d | %-7s %-7s | %s | %2d |\n", NONULL(prefix),
              cc->index, fg, bg, color, cc->ref_count);
}

/**
 * curses_colors_dump - Log all the Curses colours
 */
void curses_colors_dump(void)
{
  color_debug(LL_DEBUG5, "\033[1;32mCursesColors:\033[0m (%d)\n", NumCursesColors);
  if (TAILQ_EMPTY(&CursesColors))
    return;

  color_debug(LL_DEBUG5, "    | Index | fg      bg      | Colour | rc |\n");

  struct CursesColor *cc = NULL;
  TAILQ_FOREACH(cc, &CursesColors, entries)
  {
    curses_color_dump(cc, "    ");
  }
}

/**
 * quoted_color_dump - Log a Quoted colour
 * @param ac      Quoted colour
 * @param q_level Quote level
 * @param prefix  Prefix for the log line
 */
void quoted_color_dump(struct AttrColor *ac, int q_level, const char *prefix)
{
  if (!ac)
    return;

  int index = ac->curses_color ? ac->curses_color->index : -1;

  if ((index >= 0) || (ac->attrs != 0))
  {
    struct Buffer *color_str = buf_pool_get();
    color_debug_log_attrcolor(ac, color_str);

    const char *attrs = color_debug_log_attrs(ac->attrs);
    color_debug(LL_DEBUG5, "%s| quoted%d | %5d | %s | 0x%08x | %s\n", prefix,
                q_level, index, buf_string(color_str), ac->attrs, attrs);

    buf_pool_release(&color_str);
  }
  else
  {
    color_debug(LL_DEBUG5, "%s| quoted%d | %5d |        |            |\n",
                prefix, q_level, index);
  }
}

/**
 * quoted_color_list_dump - Log all the Quoted colours
 */
void quoted_color_list_dump(void)
{
  color_debug(LL_DEBUG5, "\033[1;32mQuotedColors:\033[0m (%d)\n", NumQuotedColors);
  color_debug(LL_DEBUG5, "    | Name    | Index | Colour | Attrs      | Attrs\n");
  for (size_t i = 0; i < COLOR_QUOTES_MAX; i++)
  {
    quoted_color_dump(&QuotedColors[i], i, "    ");
  }
}

/**
 * simple_color_dump - Dump a Simple colour to the log
 * @param cid    Colour Id, e.g. #MT_COLOR_UNDERLINE
 * @param prefix Prefix for the log line
 */
void simple_color_dump(enum ColorId cid, const char *prefix)
{
  struct AttrColor *ac = &SimpleColors[cid];
  int index = ac->curses_color ? ac->curses_color->index : -1;
  const char *name = NULL;
  const char *compose = "";

  name = mutt_map_get_name(cid, ColorFields);
  if (!name)
  {
    name = mutt_map_get_name(cid, ComposeColorFields);
    if (name)
    {
      compose = "compose ";
    }
  }

  struct Buffer *color_str = buf_pool_get();
  color_debug_log_attrcolor(ac, color_str);

  const char *attrs_str = color_debug_log_attrs(ac->attrs);
  color_debug(LL_DEBUG5, "%s| %s%-19s | %5d | %s | 0x%08x | %s\n", prefix,
              compose, name, index, buf_string(color_str), ac->attrs, attrs_str);

  buf_pool_release(&color_str);
}

/**
 * simple_colors_dump - Dump all the Simple colours to the log
 * @param force If true, list unset colours
 */
void simple_colors_dump(bool force)
{
  color_debug(LL_DEBUG5, "\033[1;32mSimpleColors:\033[0m\n");
  color_debug(LL_DEBUG5, "    | Name                | Index | Colour | Attrs      | Attrs\n");
  for (enum ColorId cid = MT_COLOR_NONE; cid < MT_COLOR_MAX; cid++)
  {
    struct AttrColor *ac = &SimpleColors[cid];
    if (!force && !attr_color_is_set(ac))
      continue;

    simple_color_dump(cid, "    ");
  }
}

/**
 * merged_colors_dump - Dump all the Merged colours to the log
 */
void merged_colors_dump(void)
{
  attr_color_list_dump(&MergedColors, "MergedColors");
}

/**
 * regex_color_dump - Dump a Regex colour to the log
 * @param rcol   Regex to dump
 * @param prefix Prefix for the log line
 */
void regex_color_dump(struct RegexColor *rcol, const char *prefix)
{
  if (!rcol)
    return;

  struct AttrColor *ac = &rcol->attr_color;
  int index = ac->curses_color ? ac->curses_color->index : -1;

  struct Buffer *color_str = buf_pool_get();
  color_debug_log_attrcolor(ac, color_str);

  const char *attrs = color_debug_log_attrs(ac->attrs);
  color_debug(LL_DEBUG5, "%s| %5d | %s | 0x%08x | %-8s | %s\n", NONULL(prefix),
              index, buf_string(color_str), ac->attrs, attrs, rcol->pattern);

  buf_pool_release(&color_str);
}

/**
 * regex_color_list_dump - Dump one Regex's colours to the log
 * @param name Name of the Regex
 * @param rcl  RegexColorList to dump
 */
void regex_color_list_dump(const char *name, struct RegexColorList *rcl)
{
  if (!name || !rcl)
    return;

  int count = 0;
  struct RegexColor *rcol = NULL;
  STAILQ_FOREACH(rcol, rcl, entries)
  {
    count++;
  }

  color_debug(LL_DEBUG5, "\033[1;32mRegexColorList %s\033[0m (%d)\n", name, count);
  if (count == 0)
    return;

  color_debug(LL_DEBUG5, "    | Index | Colour | Attrs      | Attrs    | Pattern\n");
  STAILQ_FOREACH(rcol, rcl, entries)
  {
    regex_color_dump(rcol, "    ");
  }
}

/**
 * regex_colors_dump_all - Dump all the Regex colours to the log
 */
void regex_colors_dump_all(void)
{
  regex_color_list_dump("AttachList", &AttachList);
  regex_color_list_dump("BodyList", &BodyList);
  regex_color_list_dump("HeaderList", &HeaderList);
  regex_color_list_dump("IndexAuthorList", &IndexAuthorList);
  regex_color_list_dump("IndexCollapsedList", &IndexCollapsedList);
  regex_color_list_dump("IndexDateList", &IndexDateList);
  regex_color_list_dump("IndexFlagsList", &IndexFlagsList);
  regex_color_list_dump("IndexLabelList", &IndexLabelList);
  regex_color_list_dump("IndexList", &IndexList);
  regex_color_list_dump("IndexNumberList", &IndexNumberList);
  regex_color_list_dump("IndexSizeList", &IndexSizeList);
  regex_color_list_dump("IndexSubjectList", &IndexSubjectList);
  regex_color_list_dump("IndexTagList", &IndexTagList);
  regex_color_list_dump("IndexTagsList", &IndexTagsList);
  regex_color_list_dump("StatusList", &StatusList);
}

/**
 * attr_color_dump - Dump an Attr Colour to the log
 * @param ac     AttrColor to dump
 * @param prefix prefix for the log block
 */
void attr_color_dump(struct AttrColor *ac, const char *prefix)
{
  if (!ac)
    return;

  int index = ac->curses_color ? ac->curses_color->index : -1;

  color_t fg = COLOR_DEFAULT;
  color_t bg = COLOR_DEFAULT;
  struct CursesColor *cc = ac->curses_color;
  if (cc)
  {
    fg = cc->fg;
    bg = cc->bg;
  }
  const char *color = color_debug_log_color(fg, bg);
  const char *attrs = color_debug_log_attrs(ac->attrs);
  color_debug(LL_DEBUG5, "%s| %5d | %s | 0x%08x | %s\n", NONULL(prefix), index,
              color, ac->attrs, attrs);
}

/**
 * attr_color_list_dump - Dump all the Attr Colours to the log
 * @param acl   List of Attr colours
 * @param title Title for the log block
 */
void attr_color_list_dump(struct AttrColorList *acl, const char *title)
{
  if (!acl)
    return;

  int count = 0;
  struct AttrColor *ac = NULL;
  TAILQ_FOREACH(ac, acl, entries)
  {
    count++;
  }

  color_debug(LL_DEBUG5, "\033[1;32m%s:\033[0m (%d)\n", title, count);
  if (count == 0)
    return;

  color_debug(LL_DEBUG5, "    | Index | Colour | Attrs      | Attrs\n");

  TAILQ_FOREACH(ac, acl, entries)
  {
    attr_color_dump(ac, "    ");
  }
}

/**
 * color_debug_log_attrs - Get a string to represent some attributes in the log
 * @param attrs Attributes, e.g. A_UNDERLINE
 * @retval ptr Generated string
 *
 * @note Do not free the returned string
 */
const char *color_debug_log_attrs(int attrs)
{
  static char text[64];
  struct Mapping attr_names[] = {
    { "\033[5mBLI\033[0m", A_BLINK },
    { "\033[1mBLD\033[0m", A_BOLD },
    { "\033[0mNOR\033[0m", A_NORMAL },
    { "\033[7mREV\033[0m", A_REVERSE },
    { "\033[1mSTD\033[0m", A_STANDOUT },
    { "\033[4mUND\033[0m", A_UNDERLINE },
    { NULL, 0 },
  };

  int offset = 0;
  text[0] = '\0';
  for (int i = 0; attr_names[i].name; i++)
  {
    if (attrs & attr_names[i].value)
    {
      offset += snprintf(text + offset, sizeof(text) - offset, "%s ",
                         attr_names[i].name);
    }
  }
  return text;
}

/**
 * color_debug_log_attrcolor - XXX
 *
 * @note Do not free the returned string
 */
void color_debug_log_attrcolor(struct AttrColor *ac, struct Buffer *buf)
{
  if (ac->fg.color != -1)
  {
    switch (ac->fg.type)
    {
      case CT_SIMPLE:
      {
        buf_add_printf(buf, "\033[%dm", 30 + ac->fg.color);
        break;
      }

      case CT_PALETTE:
      {
        buf_add_printf(buf, "\033[38;5;%dm", ac->fg.color);
        break;
      }

      case CT_RGB:
      {
        const int r = (ac->fg.color >> 16) & 0xff;
        const int g = (ac->fg.color >> 8) & 0xff;
        const int b = (ac->fg.color >> 0) & 0xff;

        buf_add_printf(buf, "\033[38;2;%d;%d;%dm", r, g, b);
        break;
      }
    }
  }

  if (ac->bg.color != -1)
  {
    switch (ac->bg.type)
    {
      case CT_SIMPLE:
      {
        buf_add_printf(buf, "\033[%dm", 40 + ac->bg.color);
        break;
      }

      case CT_PALETTE:
      {
        buf_add_printf(buf, "\033[48;5;%dm", ac->bg.color);
        break;
      }

      case CT_RGB:
      {
        const int r = (ac->bg.color >> 16) & 0xff;
        const int g = (ac->bg.color >> 8) & 0xff;
        const int b = (ac->bg.color >> 0) & 0xff;

        buf_add_printf(buf, "\033[48;2;%d;%d;%dm", r, g, b);
        break;
      }
    }
  }

  buf_addstr(buf, "XXXXXX\033[0m");
}

