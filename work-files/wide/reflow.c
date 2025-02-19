#include "config.h"
#include <stdint.h>
#include <string.h>
#include "mutt/lib.h"
#include "gui/mutt_window.h"
#include "gui/reflow.h"
#include "debug/lib.h"

typedef uint16_t MuttRedrawFlags;
extern struct MuttWindow *RootWindow;

bool C_Help;
bool C_StatusOnTop;
bool OptNoCurses;

void mutt_menu_set_current_redraw_full(void)
{
}

void mutt_menu_set_current_redraw(MuttRedrawFlags redraw)
{
  if (redraw)
  {
  }
}

void widescreen(void)
{
  struct MuttWindow *root = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 24, 80); root->name = "root";
  root->state.rows = root->req_rows;
  root->state.cols = root->req_cols;

  struct MuttWindow *help        = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED); help->name = "help";
  struct MuttWindow *all_dialogs = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); all_dialogs->name = "all_dialogs";
  struct MuttWindow *message     = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED); message->name = "message";

  mutt_window_add_child(root, help);
  mutt_window_add_child(root, all_dialogs);
  mutt_window_add_child(root, message);

  struct MuttWindow *index_dlg   = mutt_window_new(MUTT_WIN_ORIENT_HORIZONTAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); index_dlg->name = "index_dlg";
  struct MuttWindow *sidebar     = mutt_window_new(MUTT_WIN_ORIENT_HORIZONTAL, MUTT_WIN_SIZE_FIXED, MUTT_WIN_SIZE_UNLIMITED, 15); sidebar->name = "sidebar";
  struct MuttWindow *right_cont  = mutt_window_new(MUTT_WIN_ORIENT_HORIZONTAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); right_cont->name = "right_cont";

  mutt_window_add_child(all_dialogs, index_dlg);
  mutt_window_add_child(index_dlg, sidebar);
  mutt_window_add_child(index_dlg, right_cont);

  struct MuttWindow *index_panel = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); index_panel->name = "index_panel";
  struct MuttWindow *index       = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); index->name = "index";
  struct MuttWindow *index_bar   = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED); index_bar->name = "index_bar";

  mutt_window_add_child(index_panel, index);
  mutt_window_add_child(index_panel, index_bar);

  struct MuttWindow *pager_panel = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); pager_panel->name = "pager_panel";
  struct MuttWindow *pager       = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); pager->name = "pager";
  struct MuttWindow *pager_bar   = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED); pager_bar->name = "pager_bar";

  mutt_window_add_child(pager_panel, pager);
  mutt_window_add_child(pager_panel, pager_bar);

  mutt_window_add_child(right_cont, index_panel);
  mutt_window_add_child(right_cont, pager_panel);

  window_reflow(root);
  RootWindow = root;
  debug_win_dump();
  mutt_window_free(&root);
}

void classic(void)
{
  struct MuttWindow *root        = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 24, 80); root->name = "root";
  root->state.rows               = root->req_rows;
  root->state.cols               = root->req_cols;

  struct MuttWindow *help        = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED); help->name = "help";
  struct MuttWindow *all_dialogs = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); all_dialogs->name = "all_dialogs";
  struct MuttWindow *message     = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED); message->name = "message";

  mutt_window_add_child(root, help);
  mutt_window_add_child(root, all_dialogs);
  mutt_window_add_child(root, message);

  struct MuttWindow *index_dlg   = mutt_window_new(MUTT_WIN_ORIENT_HORIZONTAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); index_dlg->name = "index_dlg";
  struct MuttWindow *sidebar     = mutt_window_new(MUTT_WIN_ORIENT_HORIZONTAL, MUTT_WIN_SIZE_FIXED, MUTT_WIN_SIZE_UNLIMITED, 15); sidebar->name = "sidebar";
  struct MuttWindow *right_cont  = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); right_cont->name = "right_cont";

  mutt_window_add_child(all_dialogs, index_dlg);
  mutt_window_add_child(index_dlg, sidebar);
  mutt_window_add_child(index_dlg, right_cont);

  struct MuttWindow *index_panel = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MINIMISE, 0, 0); index_panel->name = "index_panel";
  struct MuttWindow *index       = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 5, MUTT_WIN_SIZE_UNLIMITED); index->name = "index";
  struct MuttWindow *index_bar   = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED); index_bar->name = "index_bar";

  mutt_window_add_child(index_panel, index);
  mutt_window_add_child(index_panel, index_bar);

  struct MuttWindow *pager_panel = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); pager_panel->name = "pager_panel";
  struct MuttWindow *pager       = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_MAXIMISE, MUTT_WIN_SIZE_UNLIMITED, MUTT_WIN_SIZE_UNLIMITED); pager->name = "pager";
  struct MuttWindow *pager_bar   = mutt_window_new(MUTT_WIN_ORIENT_VERTICAL, MUTT_WIN_SIZE_FIXED, 1, MUTT_WIN_SIZE_UNLIMITED); pager_bar->name = "pager_bar";

  mutt_window_add_child(pager_panel, pager);
  mutt_window_add_child(pager_panel, pager_bar);

  mutt_window_add_child(right_cont, index_panel);
  mutt_window_add_child(right_cont, pager_panel);

  window_reflow(root);
  RootWindow = root;
  debug_win_dump();
  mutt_window_free(&root);
}

int main()
{
  widescreen();
  classic();
  return 0;
}
