void dump_regex_color(int cid)
{
  struct RegexColorList *rcl = regex_colors_get_list(cid);

  struct Buffer *swatch = buf_pool_get();
  struct Buffer *name = buf_pool_get();
  char color_fg[64] = { 0 };
  char color_bg[64] = { 0 };
  struct RegexColor *rcol = NULL;

  color_get_name(cid, name);
  printf("\033[1;33m%s\033[0m\n", buf_string(name));

  STAILQ_FOREACH(rcol, rcl, entries)
  {
    struct AttrColor *ac = &rcol->attr_color;

    color_log_color_attrs(ac, swatch);

    printf("    %-12s %-16s %-16s %-10s # %s\n", color_log_attrs_list(ac->attrs),
           color_log_name(color_fg, sizeof(color_fg), &ac->fg),
           color_log_name(color_bg, sizeof(color_bg), &ac->bg),
           NONULL(rcol->pattern), buf_string(swatch));
  }
  buf_pool_release(&name);
  buf_pool_release(&swatch);
}

#if 0
  static const char *cmds[] = {
    "color body           red     green",
    "color body underline blue    yellow  apple",
    "color body reverse   cyan    magenta banana",
    NULL,
  };

  expected = "body:(;rg;),(u;by;A),(r;cm;B)";

  execute_commands(cmds);

  printf("\n");
  dump_regex_color(MT_COLOR_BODY);
  printf("\n");
  rcl_serialise(MT_COLOR_BODY, buf);
  printf("%s\n", buf_string(buf));
  printf("\n");

  TEST_CHECK_STR_EQ(buf_string(buf), expected);
#endif

