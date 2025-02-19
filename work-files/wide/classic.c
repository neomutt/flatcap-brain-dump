void classic(void)
{
  struct MuttWindow *index_dlg   = mutt_window_new(MUTT_WIN_ORIENT_HORIZONTAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED);
  struct MuttWindow *win_sidebar = mutt_window_new(MUTT_WIN_ORIENT_HORIZONTAL, MUTT_WIN_SIZE_FIXED, MUTT_WIN_SIZE_UNLIMITED, 15);
  struct MuttWindow *cont_right  = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED);

  mutt_window_add_child(all_dialogs, index_dlg);
  mutt_window_add_child(index_dlg, win_sidebar);
  mutt_window_add_child(index_dlg, cont_right);

  struct MuttWindow *panel_index = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MINIMISE, 0, 0);
  struct MuttWindow *win_index   = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 5, MUTT_WIN_SIZE_UNLIMITED);
  struct MuttWindow *win_ibar    = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED);

  mutt_window_add_child(panel_index, win_index);
  mutt_window_add_child(panel_index, win_ibar);

  struct MuttWindow *panel_pager = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED);
  struct MuttWindow *win_pager   = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED);
  struct MuttWindow *win_pbar    = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED);

  mutt_window_add_child(panel_pager, win_pager);
  mutt_window_add_child(panel_pager, win_pbar);

  mutt_window_add_child(cont_right, panel_index);
  mutt_window_add_child(cont_right, panel_pager);
}
