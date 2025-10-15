
bool check_empty_help(struct CliHelp *ch)
{
  if (!ch)
    return true;

  if (ch->is_set)
    return false;
  if (ch->help)
    return false;
  if (ch->version)
    return false;
  if (ch->license)
    return false;

  return true;
}

bool check_empty_config(struct CliConfig *cc)
{
  if (!cc)
    return true;

  if (cc->is_set)
    return false;
  if (cc->disable_system)
    return false;

  if (!buf_is_empty(&cc->user_file))
    return false;
  return true;
}

bool check_empty_logging(struct CliLogging *cl)
{
  if (!cl)
    return true;

  if (cl->is_set)
    return false;

  if (!buf_is_empty(&cl->log_level))
    return false;
  if (!buf_is_empty(&cl->log_file))
    return false;

  return true;
}

bool check_empty_info(struct CliInfo *ci)
{
  if (!ci)
    return true;

  if (ci->is_set)
    return false;
  if (ci->dump_config)
    return false;
  if (ci->dump_changed)
    return false;
  if (ci->show_help)
    return false;
  if (ci->hide_sensitive)
    return false;

  if (!STAILQ_EMPTY(&ci->alias_queries))
    return false;
  if (!STAILQ_EMPTY(&ci->queries))
    return false;

  return true;
}

bool check_empty_send(struct CliSend *cs)
{
  if (!cs)
    return true;

  if (cs->is_set)
    return false;

  if (!STAILQ_EMPTY(&cs->attach))
    return false;
  if (!STAILQ_EMPTY(&cs->bcc_list))
    return false;
  if (!STAILQ_EMPTY(&cs->cc_list))
    return false;
  if (!STAILQ_EMPTY(&cs->addresses))
    return false;

  if (!buf_is_empty(&cs->draft_file))
    return false;
  if (!buf_is_empty(&cs->include_file))
    return false;
  if (!buf_is_empty(&cs->subject))
    return false;

  return true;
}

bool check_empty_gui(struct CliGui *cg)
{
  if (!cg)
    return true;

  if (cg->is_set)
    return false;
  if (cg->read_only)
    return false;
  if (cg->start_postponed)
    return false;
  if (cg->start_browser)
    return false;
  if (cg->start_nntp)
    return false;
  if (cg->start_new_mail)
    return false;
  if (cg->start_any_mail)
    return false;

  if (!STAILQ_EMPTY(&cg->commands))
    return false;

  if (!buf_is_empty(&cg->folder))
    return false;
  if (!buf_is_empty(&cg->nntp_server))
    return false;
  if (!buf_is_empty(&cg->mbox_type))
    return false;

  return true;
}


