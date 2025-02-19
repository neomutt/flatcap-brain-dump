struct KeyEvent km_dokey_event(enum MenuType mtype)
{
  struct KeyEvent event = { 0, OP_NULL };
  struct Keymap *map = STAILQ_FIRST(&Keymaps[mtype]);
  int pos = 0;
  int n = 0;

  while (true)
  {
    event = mutt_getch_timeout(1000);

    /* hide timeouts, but not window resizes, from the line editor. */
    if ((event.op == OP_TIMEOUT) && !SigWinch)
      continue;

    if ((event.op == OP_TIMEOUT) || (event.op == OP_ABORT))
    {
      return event;
    }

    /* do we have an op already? */
    if (event.op != OP_NULL)
    {
      const char *func = NULL;
      const struct MenuFuncOp *funcs = NULL;

      /* is this a valid op for this menu type? */
      if ((funcs = km_get_table(mtype)) && (func = mutt_get_func(funcs, event.op)))
        return event;

      /* Sigh. Valid function but not in this context.
       * Find the literal string and push it back */
      for (i = 0; MenuNames[i].name; i++)
      {
        funcs = km_get_table(MenuNames[i].value);
        if (funcs)
        {
          func = mutt_get_func(funcs, event.op);
          if (func)
          {
            mutt_unget_ch('>');
            mutt_unget_string(func);
            mutt_unget_ch('<');
            break;
          }
        }
      }
      /* continue to chew */
      if (func)
        continue;
    }

    if (!map)
      return event;

    /* Nope. Business as usual */
    while (event.ch > map->keys[pos])
    {
      if ((pos > map->eq) || !STAILQ_NEXT(map, entries))
        return retry_generic(mtype, map->keys, pos, event.ch);
      map = STAILQ_NEXT(map, entries);
    }

    if (event.ch != map->keys[pos])
      return retry_generic(mtype, map->keys, pos, event.ch);

    if (++pos == map->len)
    {
      if (map->op != OP_MACRO)
        return (struct KeyEvent){ event.ch, map->op };

      /* OptIgnoreMacroEvents turns off processing the MacroEvents buffer
       * in mutt_getch().  Generating new macro events during that time would
       * result in undesired behavior once the option is turned off.
       *
       * Originally this returned -1, however that results in an unbuffered
       * username or password prompt being aborted.  Returning OP_NULL allows
       * mutt_enter_string_full() to display the keybinding pressed instead.
       *
       * It may be unexpected for a macro's keybinding to be returned,
       * but less so than aborting the prompt.  */
      if (OptIgnoreMacroEvents)
      {
        return (struct KeyEvent){ event.ch, OP_NULL };
      }

      if (n++ == 10)
      {
        mutt_flushinp();
        mutt_error(_("Macro loop detected"));
        return (struct KeyEvent){ '\0', OP_ABORT };
      }

      generic_tokenize_push_string(map->macro, mutt_push_macro_event);
      map = STAILQ_FIRST(&Keymaps[mtype]);
      pos = 0;
    }
  }
}

