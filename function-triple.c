struct Functions EditorFunctions[] = {
  // clang-format off
  { "backspace",       OP_EDITOR_BACKSPACE,       op_editor_backspace,       "\010", /* <Ctrl-H> */ N_("delete the char in front of the cursor") },
  { "backward-char",   OP_EDITOR_BACKWARD_CHAR,   op_editor_backward_char,   "\002", /* <Ctrl-B> */ N_("move the cursor one character to the left") },
  { "backward-word",   OP_EDITOR_BACKWARD_WORD,   op_editor_backward_word,   "\033b" /* <Alt-b>  */ N_("move the cursor to the beginning of the word") },
  { "bol",             OP_EDITOR_BOL,             op_editor_bol,             "\001", /* <Ctrl-A> */ N_("jump to the beginning of the line") },
  { "capitalize-word", OP_EDITOR_CAPITALIZE_WORD, op_editor_capitalize_word, "\033c" /* <Alt-c>  */ N_("capitalize the word") },
  { "complete",        OP_EDITOR_COMPLETE,        op_editor_complete,        "\t",   /* <Tab>    */ N_("complete filename or alias") },
  { "complete-query",  OP_EDITOR_COMPLETE_QUERY,  op_editor_complete,        "\024", /* <Ctrl-T> */ N_("complete address with query") },
  { "delete-char",     OP_EDITOR_DELETE_CHAR,     op_editor_delete_char,     "\004", /* <Ctrl-D> */ N_("delete the char under the cursor") },
  { "downcase-word",   OP_EDITOR_DOWNCASE_WORD,   op_editor_capitalize_word, "\033l" /* <Alt-l>  */ N_("convert the word to lower case") },
  { "eol",             OP_EDITOR_EOL,             op_editor_eol,             "\005", /* <Ctrl-E> */ N_("jump to the end of the line") },
  { "forward-char",    OP_EDITOR_FORWARD_CHAR,    op_editor_forward_char,    "\006", /* <Ctrl-F> */ N_("move the cursor one character to the right") },
  { "forward-word",    OP_EDITOR_FORWARD_WORD,    op_editor_forward_word,    "\033f" /* <Alt-f>  */ N_("move the cursor to the end of the word") },
  { "history-down",    OP_EDITOR_HISTORY_DOWN,    op_editor_history_down,    "\016", /* <Ctrl-N> */ N_("scroll down through the history list") },
  { "history-search",  OP_EDITOR_HISTORY_SEARCH,  op_editor_history_search,  "\022", /* <Ctrl-R> */ N_("search through the history list") },
  { "history-up",      OP_EDITOR_HISTORY_UP,      op_editor_history_up,      "\020", /* <Ctrl-P> */ N_("scroll up through the history list") },
  { "kill-eol",        OP_EDITOR_KILL_EOL,        op_editor_kill_eol,        "\013", /* <Ctrl-K> */ N_("delete chars from cursor to end of line") },
  { "kill-eow",        OP_EDITOR_KILL_EOW,        op_editor_kill_eow,        "\033d" /* <Alt-d>  */ N_("delete chars from the cursor to the end of the word") },
  { "kill-line",       OP_EDITOR_KILL_LINE,       op_editor_kill_line,       "\025", /* <Ctrl-U> */ N_("delete all chars on the line") },
  { "kill-word",       OP_EDITOR_KILL_WORD,       op_editor_kill_word,       "\027", /* <Ctrl-W> */ N_("delete the word in front of the cursor") },
  { "mailbox-cycle",   OP_EDITOR_MAILBOX_CYCLE,   op_editor_mailbox_cycle,   " ",    /* <Space>  */ N_("cycle among incoming mailboxes") },
  { "quote-char",      OP_EDITOR_QUOTE_CHAR,      op_editor_quote_char,      "\026", /* <Ctrl-V> */ N_("quote the next typed key") },
  { "transpose-chars", OP_EDITOR_TRANSPOSE_CHARS, op_editor_transpose_chars, NULL,                  N_("transpose character under cursor with previous") },
  { "upcase-word",     OP_EDITOR_UPCASE_WORD,     op_editor_capitalize_word, "\033u" /* <Alt-u>  */ N_("convert the word to upper case") },

  // Synonyms
  { "buffy-cycle",     OP_EDITOR_MAILBOX_CYCLE },

  { NULL },
  // clang-format on
};
