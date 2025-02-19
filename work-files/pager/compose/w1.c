case OP_COMPOSE_WRITE_MESSAGE:
{
  struct Mailbox *m = ctx_mailbox(Contex2);
  mutt_buffer_reset(&fname);
  if (m)
  {
    mutt_buffer_strcpy(&fname, mailbox_path(m));
    mutt_buffer_pretty_mailbox(&fname);
  }
  if (actx->idxlen)
    e->body = actx->idx[0]->body;
  if ((mutt_buffer_enter_fname(_("Write message to mailbox"), &fname, true, m,
                               false, NULL, NULL, MUTT_SEL_NO_FLAGS) != -1) &&
      !mutt_buffer_is_empty(&fname))
  {
    mutt_message(_("Writing message to %s ..."), mutt_buffer_string(&fname));
    mutt_buffer_expand_path(&fname);

    if (e->body->next)
      e->body = mutt_make_multipart(e->body);

    if (mutt_write_fcc(mutt_buffer_string(&fname), e, NULL, false, NULL, NULL, sub) == 0)
      mutt_message(_("Message written"));

    e->body = mutt_remove_multipart(e->body);
  }
  break;
}
