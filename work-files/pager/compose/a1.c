case OP_COMPOSE_ATTACH_MESSAGE:
case OP_COMPOSE_ATTACH_NEWS_MESSAGE:
{
  struct Mailbox *m_cur = ctx_mailbox(Contex2);
  mutt_buffer_reset(&fname);
  char *prompt = _("Open mailbox to attach message from");

  OptNews = false;
  if (m_cur && (op == OP_COMPOSE_ATTACH_NEWS_MESSAGE))
  {
    const char *c_news_server = cs_subset_string(sub, "news_server");
    CurrentNewsSrv = nntp_select_server(m_cur, c_news_server, false);
    if (!CurrentNewsSrv)
      break;

    prompt = _("Open newsgroup to attach message from");
    OptNews = true;
  }

  if (m_cur)
  {
    if ((op == OP_COMPOSE_ATTACH_MESSAGE) ^ (m_cur->type == MUTT_NNTP))
    {
      mutt_buffer_strcpy(&fname, mailbox_path(m_cur));
      mutt_buffer_pretty_mailbox(&fname);
    }
  }

  if ((mutt_buffer_enter_fname(prompt, &fname, true, m_cur, false, NULL, NULL,
                               MUTT_SEL_NO_FLAGS) == -1) ||
      mutt_buffer_is_empty(&fname))
  {
    break;
  }

  if (OptNews)
    nntp_expand_path(fname.data, fname.dsize, &CurrentNewsSrv->conn->account);
  else
    mutt_buffer_expand_path(&fname);
  if (imap_path_probe(mutt_buffer_string(&fname), NULL) != MUTT_IMAP)
  {
    if (pop_path_probe(mutt_buffer_string(&fname), NULL) != MUTT_POP)
    {
      if (!OptNews && (nntp_path_probe(mutt_buffer_string(&fname), NULL) != MUTT_NNTP))
      {
        if (mx_path_probe(mutt_buffer_string(&fname)) != MUTT_NOTMUCH)
        {
          /* check to make sure the file exists and is readable */
          if (access(mutt_buffer_string(&fname), R_OK) == -1)
          {
            mutt_perror(mutt_buffer_string(&fname));
            break;
          }
        }
      }
    }
  }

  menu->redraw = REDRAW_FULL;

  struct Mailbox *m_att = mx_path_resolve(mutt_buffer_string(&fname));
  bool old_readonly = m_att->readonly;
  struct Context *ctx_att = mx_mbox_open(m_att, MUTT_READONLY);
  if (!ctx_att)
  {
    mutt_error(_("Unable to open mailbox %s"), mutt_buffer_string(&fname));
    mx_fastclose_mailbox(m_att);
    m_att = NULL;
    break;
  }

  if (ctx_att->mailbox->msg_count == 0)
  {
    mx_mbox_close(&ctx_att);
    mutt_error(_("No messages in that folder"));
    break;
  }

  struct Context *ctx_cur = Contex2; /* remember current folder and sort methods */
  const enum SortType old_sort = cs_subset_sort(sub, "sort"); /* `$sort`, `$sort_aux` could be changed in mutt_index_menu() */
  const enum SortType old_sort_aux = cs_subset_sort(sub, "sort_aux");

  Contex2 = ctx_att;
  OptAttachMsg = true;
  mutt_message(_("Tag the messages you want to attach"));
  struct MuttWindow *dlgindex = index_pager_init();
  dialog_push(dlgindex);
  mutt_index_menu(dlgindex);
  dialog_pop();
  index_pager_shutdown(dlgindex);
  mutt_window_free(&dlgindex);
  OptAttachMsg = false;

  if (!Contex2)
  {
    /* go back to the folder we started from */
    Contex2 = ctx_cur;
    /* Restore old $sort and $sort_aux */
    if (old_sort != cs_subset_sort(sub, "sort"))
      cs_subset_str_native_set(sub, "sort", old_sort, NULL);
    if (old_sort_aux != cs_subset_sort(sub, "sort_aux"))
      cs_subset_str_native_set(sub, "sort_aux", old_sort_aux, NULL);
    menu->redraw |= REDRAW_INDEX | REDRAW_STATUS;
    break;
  }

  bool added_attachment = false;
  for (int i = 0; i < Contex2->mailbox->msg_count; i++)
  {
    if (!Contex2->mailbox->emails[i])
      break;
    if (!message_is_tagged(Contex2->mailbox->emails[i]))
      continue;

    struct AttachPtr *ap = mutt_mem_calloc(1, sizeof(struct AttachPtr));
    ap->body = mutt_make_message_attach(Contex2->mailbox, Contex2->mailbox->emails[i], true, sub);
    if (ap->body)
    {
      added_attachment = true;
      update_idx(menu, actx, ap);
    }
    else
    {
      mutt_error(_("Unable to attach"));
      FREE(&ap);
    }
  }
  menu->redraw |= REDRAW_FULL;

  Contex2->mailbox->readonly = old_readonly;
  mx_fastclose_mailbox(Contex2->mailbox);
  ctx_free(&Contex2);

  /* go back to the folder we started from */
  Contex2 = ctx_cur;
  /* Restore old $sort and $sort_aux */
  if (old_sort != cs_subset_sort(sub, "sort"))
    cs_subset_str_native_set(sub, "sort", old_sort, NULL);
  if (old_sort_aux != cs_subset_sort(sub, "sort_aux"))
    cs_subset_str_native_set(sub, "sort_aux", old_sort_aux, NULL);
  if (added_attachment)
    mutt_message_hook(NULL, e, MUTT_SEND2_HOOK);
  break;
}
