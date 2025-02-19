#ifdef USE_SLANG_CURSES
  else if (*s == '#')
  {
    s += 1;
    *col = strtoul(s, &eptr, 16);
    if ((*s == '\0') || (*eptr != '\0') ||
        ((*col == COLOR_UNSET) && !OptNoCurses && has_colors()))
    {
      snprintf(err->data, err->dsize, _("%s: color not supported by term"), s);
      return MUTT_CMD_ERROR;
    }
    *col |= RGB24;
  }
#endif
