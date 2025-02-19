static void cli_dump_bool(const char *label, bool b)
{
  printf("\t%s: %s\n", label, b ? "true" : "false");
}

static void cli_dump_buffer(const char *label, struct Buffer *buf)
{
  printf("\t%s: ", label);
  if (buf_is_empty(buf))
    printf("-\n");
  else
    printf("'%s'\n", buf_string(buf));
}

static void cli_dump_list(const char *label, const struct ListHead *lh)
{
  printf("\t%s: ", label);

  if (STAILQ_EMPTY(lh))
  {
    printf("-\n");
    return;
  }

  struct ListNode *np = NULL;
  STAILQ_FOREACH(np, lh, entries)
  {
    printf("'%s'", np->data);
    if (STAILQ_NEXT(np, entries))
      printf(", ");
  }
  printf("\n");
}

static void cli_dump_help(struct CliHelp *ch)
{
  if (!ch->is_set)
    return;

  printf("Help\n");

  cli_dump_bool("help", ch->help);
  cli_dump_bool("version", ch->version);
  cli_dump_bool("license", ch->license);
}

static void cli_dump_config(struct CliConfig *cc)
{
  if (!cc->is_set)
    return;

  printf("Config\n");

  cli_dump_bool("disable_system", cc->disable_system);
  cli_dump_buffer("user_file", &cc->user_file);
}

static void cli_dump_logging(struct CliLogging *cl)
{
  if (!cl->is_set)
    return;

  printf("Logging\n");

  cli_dump_buffer("log_level", &cl->log_level);
  cli_dump_buffer("log_file", &cl->log_file);
}

static void cli_dump_info(struct CliInfo *ci)
{
  if (!ci->is_set)
    return;

  printf("Info\n");

  cli_dump_bool("dump_config", ci->dump_config);
  cli_dump_bool("dump_changed", ci->dump_changed);
  cli_dump_bool("show_help", ci->show_help);
  cli_dump_bool("hide_sensitive", ci->hide_sensitive);

  cli_dump_list("alias_queries", &ci->alias_queries);
  cli_dump_list("queries", &ci->queries);
}

static void cli_dump_send(struct CliSend *cs)
{
  if (!cs->is_set)
    return;

  printf("Send\n");

  cli_dump_list("attach", &cs->attach);
  cli_dump_list("bcc_list", &cs->bcc_list);
  cli_dump_list("cc_list", &cs->cc_list);
  cli_dump_list("addresses", &cs->addresses);

  cli_dump_bool("use_crypto", cs->use_crypto);
  cli_dump_bool("edit_infile", cs->edit_infile);

  cli_dump_buffer("draft_file", &cs->draft_file);
  cli_dump_buffer("include_file", &cs->include_file);
  cli_dump_buffer("subject", &cs->subject);
}

static void cli_dump_gui(struct CliGui *cg)
{
  if (!cg->is_set)
    return;

  printf("Gui\n");

  cli_dump_bool("read_only", cg->read_only);
  cli_dump_bool("start_postponed", cg->start_postponed);
  cli_dump_bool("start_browser", cg->start_browser);
  cli_dump_bool("start_nntp", cg->start_nntp);
  cli_dump_bool("start_new_mail", cg->start_new_mail);
  cli_dump_bool("start_any_mail", cg->start_any_mail);

  cli_dump_list("commands", &cg->commands);

  cli_dump_buffer("folder", &cg->folder);
  cli_dump_buffer("nntp_server", &cg->nntp_server);
  cli_dump_buffer("mbox_type", &cg->mbox_type);
}

static void cli_dump(struct CommandLine *cli)
{
  printf("CommandLine\n");

  cli_dump_help(&cli->help);
  cli_dump_config(&cli->config);
  cli_dump_logging(&cli->logging);
  cli_dump_info(&cli->info);
  cli_dump_send(&cli->send);
  cli_dump_gui(&cli->gui);
}

