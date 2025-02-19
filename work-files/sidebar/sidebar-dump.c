  struct SbEntry **sbep = NULL;
  mutt_debug(LL_DEBUG1, "----------------------------------------\n");
  mutt_debug(LL_DEBUG1, "entries (%d, T%d, O%d, H%d, B%d)\n", ARRAY_SIZE(&wdata->entries), wdata->top_index, wdata->opn_index, wdata->hil_index, wdata->bot_index);
  ARRAY_FOREACH(sbep, &wdata->entries)
  {
    char c = ' ';
    if (ARRAY_FOREACH_IDX == wdata->top_index) c = 'T';
    if (ARRAY_FOREACH_IDX == wdata->bot_index) c = 'B';
    if (ARRAY_FOREACH_IDX == wdata->hil_index) c = 'H';
    if (ARRAY_FOREACH_IDX == wdata->opn_index) c = 'O';
    struct SbEntry *entry = (*sbep);
    struct Mailbox *m = entry->mailbox;
    if (entry && m)
      mutt_debug(LL_DEBUG1, "    [%c] S%d, M%d, %s\n", c, entry->is_hidden, m->flags, strrchr(mutt_b2s(&m->pathbuf), '/'));
    else
      mutt_debug(LL_DEBUG1, "    NONE\n");
  }
  mutt_debug(LL_DEBUG1, "----------------------------------------\n");

