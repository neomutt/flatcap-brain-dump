op_editor_history_up()
{
  wdata.state->curpos = wdata.state->lastchar;
  if (mutt_hist_at_scratch(wdata.hclass))
  {
    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf, wdata.state->curpos);
    mutt_hist_save_scratch(wdata.hclass, wdata.buf);
  }
  replace_part(wdata.state, 0, mutt_hist_prev(wdata.hclass));
  wdata.redraw = ENTER_REDRAW_INIT;
}

op_editor_history_down()
{
  wdata.state->curpos = wdata.state->lastchar;
  if (mutt_hist_at_scratch(wdata.hclass))
  {
    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf, wdata.state->curpos);
    mutt_hist_save_scratch(wdata.hclass, wdata.buf);
  }
  replace_part(wdata.state, 0, mutt_hist_next(wdata.hclass));
  wdata.redraw = ENTER_REDRAW_INIT;
}

op_editor_history_search()
{
  wdata.state->curpos = wdata.state->lastchar;
  mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf, wdata.state->curpos);
  mutt_hist_complete(wdata.buf, wdata.buflen, wdata.hclass);
  replace_part(wdata.state, 0, wdata.buf);
  rc = 1;
  goto bye;
}

op_editor_backspace()
{
  if (wdata.state->curpos == 0)
  {
    // Pressing backspace when no text is in the command prompt should exit the prompt
    const bool c_abort_backspace =
        cs_subset_bool(NeoMutt->sub, "abort_backspace");
    if (c_abort_backspace && (wdata.state->lastchar == 0))
      goto bye;
    // Pressing backspace with text in the command prompt should just beep
    mutt_beep(false);
  }
  else
  {
    size_t i = wdata.state->curpos;
    while ((i > 0) && COMB_CHAR(wdata.state->wbuf[i - 1]))
      i--;
    if (i > 0)
      i--;
    memmove(wdata.state->wbuf + i, wdata.state->wbuf + wdata.state->curpos,
            (wdata.state->lastchar - wdata.state->curpos) * sizeof(wchar_t));
    wdata.state->lastchar -= wdata.state->curpos - i;
    wdata.state->curpos = i;
  }
}

op_editor_bol()
{
  wdata.state->curpos = 0;
}

op_editor_eol()
{
  wdata.redraw = ENTER_REDRAW_INIT;
}

op_editor_kill_line()
{
  wdata.state->curpos = 0;
  wdata.state->lastchar = 0;
}

op_editor_kill_eol()
{
  wdata.state->lastchar = wdata.state->curpos;
}

op_editor_backward_char()
{
  if (wdata.state->curpos == 0)
    mutt_beep(false);
  else
  {
    while (wdata.state->curpos && COMB_CHAR(wdata.state->wbuf[wdata.state->curpos - 1]))
      wdata.state->curpos--;
    if (wdata.state->curpos)
      wdata.state->curpos--;
  }
}

op_editor_forward_char()
{
  if (wdata.state->curpos == wdata.state->lastchar)
    mutt_beep(false);
  else
  {
    wdata.state->curpos++;
    while ((wdata.state->curpos < wdata.state->lastchar) &&
           COMB_CHAR(wdata.state->wbuf[wdata.state->curpos]))
    {
      wdata.state->curpos++;
    }
  }
}

op_editor_backward_word()
{
  if (wdata.state->curpos == 0)
    mutt_beep(false);
  else
  {
    while (wdata.state->curpos && iswspace(wdata.state->wbuf[wdata.state->curpos - 1]))
      wdata.state->curpos--;
    while (wdata.state->curpos && !iswspace(wdata.state->wbuf[wdata.state->curpos - 1]))
      wdata.state->curpos--;
  }
}

op_editor_forward_word()
{
  if (wdata.state->curpos == wdata.state->lastchar)
    mutt_beep(false);
  else
  {
    while ((wdata.state->curpos < wdata.state->lastchar) &&
           iswspace(wdata.state->wbuf[wdata.state->curpos]))
    {
      wdata.state->curpos++;
    }
    while ((wdata.state->curpos < wdata.state->lastchar) &&
           !iswspace(wdata.state->wbuf[wdata.state->curpos]))
    {
      wdata.state->curpos++;
    }
  }
}

op_editor_capitalize_word()
{
  if (wdata.state->curpos == wdata.state->lastchar)
  {
    mutt_beep(false);
    break;
  }
  while (wdata.state->curpos && !iswspace(wdata.state->wbuf[wdata.state->curpos]))
    wdata.state->curpos--;
  while ((wdata.state->curpos < wdata.state->lastchar) && iswspace(wdata.state->wbuf[wdata.state->curpos]))
    wdata.state->curpos++;
  while ((wdata.state->curpos < wdata.state->lastchar) &&
         !iswspace(wdata.state->wbuf[wdata.state->curpos]))
  {
    if (ch == OP_EDITOR_DOWNCASE_WORD)
      wdata.state->wbuf[wdata.state->curpos] = towlower(wdata.state->wbuf[wdata.state->curpos]);
    else
    {
      wdata.state->wbuf[wdata.state->curpos] = towupper(wdata.state->wbuf[wdata.state->curpos]);
      if (ch == OP_EDITOR_CAPITALIZE_WORD)
        ch = OP_EDITOR_DOWNCASE_WORD;
    }
    wdata.state->curpos++;
  }
}

op_editor_delete_char()
{
  if (wdata.state->curpos == wdata.state->lastchar)
    mutt_beep(false);
  else
  {
    size_t i = wdata.state->curpos;
    while ((i < wdata.state->lastchar) && COMB_CHAR(wdata.state->wbuf[i]))
      i++;
    if (i < wdata.state->lastchar)
      i++;
    while ((i < wdata.state->lastchar) && COMB_CHAR(wdata.state->wbuf[i]))
      i++;
    memmove(wdata.state->wbuf + wdata.state->curpos, wdata.state->wbuf + i,
            (wdata.state->lastchar - i) * sizeof(wchar_t));
    wdata.state->lastchar -= i - wdata.state->curpos;
  }
}

op_editor_kill_word()
{
  /* delete to beginning of word */
  if (wdata.state->curpos != 0)
  {
    size_t i = wdata.state->curpos;
    while (i && iswspace(wdata.state->wbuf[i - 1]))
      i--;
    if (i > 0)
    {
      if (iswalnum(wdata.state->wbuf[i - 1]))
      {
        for (--i; (i > 0) && iswalnum(wdata.state->wbuf[i - 1]); i--)
          ; // do nothing
      }
      else
        i--;
    }
    memmove(wdata.state->wbuf + i, wdata.state->wbuf + wdata.state->curpos,
            (wdata.state->lastchar - wdata.state->curpos) * sizeof(wchar_t));
    wdata.state->lastchar += i - wdata.state->curpos;
    wdata.state->curpos = i;
  }
}

op_editor_kill_eow()
{
  /* delete to end of word */

  /* wdata.first skip over whitespace */
  size_t i;
  for (i = wdata.state->curpos; (i < wdata.state->lastchar) && iswspace(wdata.state->wbuf[i]); i++)
    ; // do nothing

  /* if there are any characters left.. */
  if (i < wdata.state->lastchar)
  {
    /* if the current character is alphanumeric.. */
    if (iswalnum(wdata.state->wbuf[i]))
    {
      /* skip over the rest of the word consistent of only alphanumerics */
      for (; (i < wdata.state->lastchar) && iswalnum(wdata.state->wbuf[i]); i++)
        ; // do nothing
    }
    else
    {
      /* skip over one non-alphanumeric character */
      i++;
    }
  }

  memmove(wdata.state->wbuf + wdata.state->curpos, wdata.state->wbuf + i,
      (wdata.state->lastchar - i) * sizeof(wchar_t));
  wdata.state->lastchar += wdata.state->curpos - i;
}

op_editor_mailbox_cycle()
{
  if (wdata.flags & MUTT_COMP_FILE_MBOX)
  {
    wdata.first = true; /* clear input if user types a real key later */
    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf, wdata.state->curpos);

    struct Buffer *pool = mutt_buffer_pool_get();
    mutt_buffer_addstr(pool, wdata.buf);
    mutt_mailbox_next(wdata.m, pool);
    mutt_str_copy(wdata.buf, mutt_buffer_string(pool), wdata.buflen);
    mutt_buffer_pool_release(&pool);

    wdata.state->curpos = wdata.state->lastchar =
        mutt_mb_mbstowcs(&wdata.state->wbuf, &wdata.state->wbuflen, 0, wdata.buf);
    break;
  }
  else if (!(wdata.flags & MUTT_COMP_FILE))
  {
    if (self_insert(&wdata))
      goto bye;
    break;
  }
  /* fallthrough */
}

op_editor_complete()
{
  wdata.state->tabs++;
  if (wdata.flags & MUTT_COMP_FILE_SIMPLE)
  {
    size_t i;
    for (i = wdata.state->curpos;
         (i > 0) && !mutt_mb_is_shell_char(wdata.state->wbuf[i - 1]); i--)
    {
    }
    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf + i, wdata.state->curpos - i);
    if (wdata.tempbuf && (wdata.templen == (wdata.state->lastchar - i)) &&
        (memcmp(wdata.tempbuf, wdata.state->wbuf + i, (wdata.state->lastchar - i) * sizeof(wchar_t)) == 0))
    {
      mutt_select_file(wdata.buf, wdata.buflen, MUTT_SEL_NO_FLAGS, wdata.m, NULL, NULL);
      if (wdata.buf[0] != '\0')
        replace_part(wdata.state, i, wdata.buf);
      rc = 1;
      goto bye;
    }
    if (mutt_complete(wdata.buf, wdata.buflen) == 0)
    {
      wdata.templen = wdata.state->lastchar - i;
      mutt_mem_realloc(&wdata.tempbuf, wdata.templen * sizeof(wchar_t));
      memcpy(wdata.tempbuf, wdata.state->wbuf + i, wdata.templen * sizeof(wchar_t));
    }
    else
      mutt_beep(false);

    replace_part(wdata.state, i, wdata.buf);
  }
  else if ((wdata.flags & MUTT_COMP_ALIAS) && (ch == OP_EDITOR_COMPLETE))
  {
    /* invoke the alias-menu to get more addresses */
    size_t i;
    for (i = wdata.state->curpos;
         (i > 0) && (wdata.state->wbuf[i - 1] != ',') && (wdata.state->wbuf[i - 1] != ':'); i--)
    {
    }
    for (; (i < wdata.state->lastchar) && (wdata.state->wbuf[i] == ' '); i++)
      ; // do nothing

    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf + i, wdata.state->curpos - i);
    int rc2 = alias_complete(wdata.buf, wdata.buflen, NeoMutt->sub);
    replace_part(wdata.state, i, wdata.buf);
    if (rc2 != 1)
    {
      rc = 1;
      goto bye;
    }
    break;
  }
  else if ((wdata.flags & MUTT_COMP_LABEL) && (ch == OP_EDITOR_COMPLETE))
  {
    size_t i;
    for (i = wdata.state->curpos;
         (i > 0) && (wdata.state->wbuf[i - 1] != ',') && (wdata.state->wbuf[i - 1] != ':'); i--)
    {
    }
    for (; (i < wdata.state->lastchar) && (wdata.state->wbuf[i] == ' '); i++)
      ; // do nothing

    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf + i, wdata.state->curpos - i);
    int rc2 = mutt_label_complete(wdata.buf, wdata.buflen, wdata.state->tabs);
    replace_part(wdata.state, i, wdata.buf);
    if (rc2 != 1)
    {
      rc = 1;
      goto bye;
    }
    break;
  }
  else if ((wdata.flags & MUTT_COMP_PATTERN) && (ch == OP_EDITOR_COMPLETE))
  {
    size_t i = wdata.state->curpos;
    if (i && (wdata.state->wbuf[i - 1] == '~'))
    {
      if (dlg_select_pattern(wdata.buf, wdata.buflen))
        replace_part(wdata.state, i - 1, wdata.buf);
      rc = 1;
      goto bye;
    }
    for (; (i > 0) && (wdata.state->wbuf[i - 1] != '~'); i--)
      ; // do nothing

    if ((i > 0) && (i < wdata.state->curpos) && (wdata.state->wbuf[i - 1] == '~') &&
        (wdata.state->wbuf[i] == 'y'))
    {
      i++;
      mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf + i, wdata.state->curpos - i);
      int rc2 = mutt_label_complete(wdata.buf, wdata.buflen, wdata.state->tabs);
      replace_part(wdata.state, i, wdata.buf);
      if (rc2 != 1)
      {
        rc = 1;
        goto bye;
      }
    }
    else
    {
      if (self_insert(&wdata))
        goto bye;
    }
    break;
  }
  else if ((wdata.flags & MUTT_COMP_ALIAS) && (ch == OP_EDITOR_COMPLETE_QUERY))
  {
    size_t i = wdata.state->curpos;
    if (i != 0)
    {
      for (; (i > 0) && (wdata.state->wbuf[i - 1] != ','); i--)
        ; // do nothing

      for (; (i < wdata.state->curpos) && (wdata.state->wbuf[i] == ' '); i++)
        ; // do nothing
    }

    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf + i, wdata.state->curpos - i);
    struct Buffer *tmp = mutt_buffer_pool_get();
    mutt_buffer_strcpy(tmp, wdata.buf);
    query_complete(tmp, NeoMutt->sub);
    mutt_str_copy(wdata.buf, mutt_buffer_string(tmp), wdata.buflen);
    mutt_buffer_pool_release(&tmp);
    replace_part(wdata.state, i, wdata.buf);

    rc = 1;
    goto bye;
  }
  else if (wdata.flags & MUTT_COMP_COMMAND)
  {
    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf, wdata.state->curpos);
    size_t i = strlen(wdata.buf);
    if ((i != 0) && (wdata.buf[i - 1] == '=') &&
        (mutt_var_value_complete(wdata.buf, wdata.buflen, i) != 0))
    {
      wdata.state->tabs = 0;
    }
    else if (mutt_command_complete(wdata.buf, wdata.buflen, i, wdata.state->tabs) == 0)
      mutt_beep(false);
    replace_part(wdata.state, 0, wdata.buf);
  }
  else if (wdata.flags & (MUTT_COMP_FILE | MUTT_COMP_FILE_MBOX))
  {
    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf, wdata.state->curpos);

    /* see if the path has changed from the last time */
    if ((!wdata.tempbuf && !wdata.state->lastchar) ||
        (wdata.tempbuf && (wdata.templen == wdata.state->lastchar) &&
         (memcmp(wdata.tempbuf, wdata.state->wbuf, wdata.state->lastchar * sizeof(wchar_t)) == 0)))
    {
      mutt_select_file(wdata.buf, wdata.buflen,
                       ((wdata.flags & MUTT_COMP_FILE_MBOX) ? MUTT_SEL_FOLDER : MUTT_SEL_NO_FLAGS) |
                           (wdata.multiple ? MUTT_SEL_MULTI : MUTT_SEL_NO_FLAGS),
                       wdata.m, wdata.files, wdata.numfiles);
      if (wdata.buf[0] != '\0')
      {
        mutt_pretty_mailbox(wdata.buf, wdata.buflen);
        if (!wdata.pass)
          mutt_hist_add(wdata.hclass, wdata.buf, true);
        rc = 0;
        goto bye;
      }

      /* file selection cancelled */
      rc = 1;
      goto bye;
    }

    if (mutt_complete(wdata.buf, wdata.buflen) == 0)
    {
      wdata.templen = wdata.state->lastchar;
      mutt_mem_realloc(&wdata.tempbuf, wdata.templen * sizeof(wchar_t));
      memcpy(wdata.tempbuf, wdata.state->wbuf, wdata.templen * sizeof(wchar_t));
    }
    else
      mutt_beep(false); /* let the user know that nothing matched */
    replace_part(wdata.state, 0, wdata.buf);
  }
#ifdef USE_NOTMUCH
  else if (wdata.flags & MUTT_COMP_NM_QUERY)
  {
    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf, wdata.state->curpos);
    size_t len = strlen(wdata.buf);
    if (!mutt_nm_query_complete(wdata.buf, wdata.buflen, len, wdata.state->tabs))
      mutt_beep(false);

    replace_part(wdata.state, 0, wdata.buf);
  }
  else if (wdata.flags & MUTT_COMP_NM_TAG)
  {
    mutt_mb_wcstombs(wdata.buf, wdata.buflen, wdata.state->wbuf, wdata.state->curpos);
    if (!mutt_nm_tag_complete(wdata.buf, wdata.buflen, wdata.state->tabs))
      mutt_beep(false);

    replace_part(wdata.state, 0, wdata.buf);
  }
#endif
  else
  {
    if (self_insert(&wdata))
      goto bye;
  }
}

op_editor_quote_char()
{
  struct KeyEvent event = { OP_NULL, OP_NULL };
  do
  {
    event = mutt_getch();
  } while (event.ch == OP_TIMEOUT);
  if (event.ch >= 0)
  {
    LastKey = event.ch;
    if (self_insert(&wdata))
      goto bye;
  }
}

op_editor_transpose_chars()
{
  if (wdata.state->lastchar < 2)
    mutt_beep(false);
  else
  {
    if (wdata.state->curpos == 0)
      wdata.state->curpos = 2;
    else if (wdata.state->curpos < wdata.state->lastchar)
      wdata.state->curpos++;

    wchar_t wc = wdata.state->wbuf[wdata.state->curpos - 2];
    wdata.state->wbuf[wdata.state->curpos - 2] = wdata.state->wbuf[wdata.state->curpos - 1];
    wdata.state->wbuf[wdata.state->curpos - 1] = wc;
  }
}
