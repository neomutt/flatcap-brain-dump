/**
 * @file
 * Sidebar Views
 *
 * @authors
 * Copyright (C) 2020 Richard Russon <rich@flatcap.org>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MUTT_SIDEBAR_VIEW_H
#define MUTT_SIDEBAR_VIEW_H

#include <stddef.h>
#include <stdbool.h>
#include "mutt/lib.h"

struct Account;
struct EventAccount;
struct Mailbox;
struct MuttWindow;

struct SidebarMailboxView
{
  struct Mailbox *mailbox;
  const char *display;
  bool visible;
  bool changed;
};

struct SidebarAccountView
{
  struct Account *account;
  const char *display;
  bool visible;
  bool changed;

  struct SidebarMailboxView **mailboxes;
  size_t num_mailboxes;
  size_t max_mailboxes;
};

struct SidebarWinData
{
  struct SidebarAccountView **accounts;
  size_t num_accounts;
  size_t max_accounts;
};

struct SidebarDisplayLine
{
  enum NotifyType type;
};

void                       sb_account_add   (struct SidebarWinData *data, struct Account *a);
void                       sb_account_dump  (struct SidebarWinData *data);
struct SidebarAccountView *sb_account_find  (struct SidebarWinData *data, struct Account *a);
void                       sb_account_free  (struct SidebarAccountView **ptr);
struct SidebarAccountView *sb_account_new   (struct Account *a);
void                       sb_account_remove(struct SidebarWinData *data, struct Account *a);
int                        sb_account       (struct MuttWindow *win, struct EventAccount *ea);
void                       sb_mailbox_add   (struct SidebarAccountView *av, struct Mailbox *m);
void                       sb_mailbox_dump  (struct SidebarAccountView *av);
void                       sb_mailbox_free  (struct SidebarMailboxView **ptr);
struct SidebarMailboxView *sb_mailbox_new   (struct Mailbox *m);
void                       sb_mailbox_remove(struct SidebarAccountView *av, struct Mailbox *m);

#endif /* MUTT_SIDEBAR_VIEW_H */
