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

/**
 * @page sidebar Sidebar Views
 *
 * Sidebar Views
 */

#include "config.h"
#include <string.h>
#include "mutt/lib.h"
#include "core/lib.h"
#include "gui/lib.h"
#include "sidebar/view.h"

/**
 * sb_mailbox_dump - XXX
 */
void sb_mailbox_dump(struct SidebarAccountView *av)
{
  for (size_t i = 0; i < av->max_mailboxes; i++)
  {
    if (i < av->num_mailboxes)
    {
      mutt_debug(LL_DEBUG1, "\tMailbox %p %s - %s\n", av->mailboxes[i],
                 av->mailboxes[i]->mailbox->name, mailbox_path(av->mailboxes[i]->mailbox));
    }
    else
    {
      if (av->mailboxes[i])
        mutt_debug(LL_DEBUG1, "\tMailbox should be NULL %p\n", av->mailboxes[i]);
    }
  }
}

/**
 * sb_mailbox_free - XXX
 */
void sb_mailbox_free(struct SidebarMailboxView **ptr)
{
  struct SidebarMailboxView *mv = *ptr;

  FREE(&mv->display);

  FREE(ptr);
}

/**
 * sb_mailbox_new - XXX
 */
struct SidebarMailboxView *sb_mailbox_new(struct Mailbox *m)
{
  struct SidebarMailboxView *mv = mutt_mem_calloc(1, sizeof(struct SidebarMailboxView));

  mv->mailbox = m;

  return mv;
}

/**
 * sb_mailbox_remove - XXX
 */
void sb_mailbox_remove(struct SidebarAccountView *av, struct Mailbox *m)
{
  size_t i;
  size_t num = av->num_mailboxes;

  for (i = 0; i < num; i++)
  {
    if (av->mailboxes[i]->mailbox == m)
      break;
  }

  if (i >= num)
    return;

  FREE(&av->mailboxes[i]);

  if (i < (num - 1))
  {
    void *dest = &av->mailboxes[i];
    void *src = &av->mailboxes[i + 1];
    size_t size = (num - i - 1) * sizeof(struct SidebarMailboxView *);
    memmove(dest, src, size);
  }

  num--;
  av->mailboxes[num] = NULL;
  av->num_mailboxes = num;
}

/**
 * sb_mailbox_add - XXX
 */
void sb_mailbox_add(struct SidebarAccountView *av, struct Mailbox *m)
{
  const int extra = 25;

  if ((av->num_mailboxes + 1) >= av->max_mailboxes)
  {
    mutt_mem_realloc(av->mailboxes, (av->max_mailboxes + extra) *
                                        sizeof(struct SidebarMailboxView *));
    memset(av->mailboxes[av->max_mailboxes], 0, extra * sizeof(struct SidebarMailboxView *));
    av->max_mailboxes += extra;
  }

  av->mailboxes[av->num_mailboxes] = sb_mailbox_new(m);
  av->num_mailboxes++;
}

/**
 * sb_account_dump - XXX
 */
void sb_account_dump(struct SidebarWinData *data)
{
  mutt_debug(LL_DEBUG1, "\n");
  for (size_t i = 0; i < data->max_accounts; i++)
  {
    if (i < data->num_accounts)
    {
      mutt_debug(LL_DEBUG1, "Account %p %s\n", data->accounts[i],
                 data->accounts[i]->account->name);
    }
    else
    {
      if (data->accounts[i])
        mutt_debug(LL_DEBUG1, "Account should be NULL %p\n", data->accounts[i]);
    }
    if (data->accounts[i] && data->accounts[i]->account)
    {
      sb_mailbox_dump(data->accounts[i]);
    }
  }
}

/**
 * sb_account_free - XXX
 */
void sb_account_free(struct SidebarAccountView **ptr)
{
  struct SidebarAccountView *av = *ptr;

  for (size_t i = 0; i < av->num_mailboxes; i++)
  {
    sb_mailbox_free(&av->mailboxes[i]);
    FREE(&av->display);
  }

  FREE(&av->mailboxes);
  FREE(ptr);
}

/**
 * sb_account_new - XXX
 */
struct SidebarAccountView *sb_account_new(struct Account *a)
{
  struct SidebarAccountView *av = mutt_mem_calloc(1, sizeof(struct SidebarAccountView));

  av->max_mailboxes = 25;
  av->mailboxes =
      mutt_mem_calloc(av->max_mailboxes, sizeof(struct SidebarMailboxView *));
  av->account = a;

  return av;
}

/**
 * sb_account_remove - XXX
 */
void sb_account_remove(struct SidebarWinData *data, struct Account *a)
{
}

/**
 * sb_account_add - XXX
 */
void sb_account_add(struct SidebarWinData *data, struct Account *a)
{
  const int extra = 25;

  if ((data->num_accounts + 1) >= data->max_accounts)
  {
    mutt_mem_realloc(data->accounts, (data->max_accounts + extra) *
                                         sizeof(struct SidebarAccountView *));
    memset(data->accounts[data->max_accounts], 0,
           extra * sizeof(struct SidebarAccountView *));
    data->max_accounts += extra;
  }

  struct SidebarAccountView *av = sb_account_new(a);
  data->accounts[data->num_accounts] = av;
  data->num_accounts++;

  struct MailboxNode *np = NULL;
  STAILQ_FOREACH(np, &a->mailboxes, entries)
  {
    sb_mailbox_add(av, np->mailbox);
  }
}

/**
 * sb_account_find - XXX
 */
struct SidebarAccountView *sb_account_find(struct SidebarWinData *data, struct Account *a)
{
  for (size_t i = 0; i < data->num_accounts; i++)
  {
    if (data->accounts[i]->account == a)
      return data->accounts[i];
  }

  return NULL;
}

/**
 * sb_account - XXX
 */
int sb_account(struct MuttWindow *win, struct EventAccount *ea)
{
  struct SidebarWinData *data = win->wdata;
  struct Account *a = ea->account;

  sb_account_add(data, a);
  sb_account_dump(data);
  return 0;
}
