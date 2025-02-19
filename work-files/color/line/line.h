/**
 * @file
 * Pager Line
 *
 * @authors
 * Copyright (C) 2021 Richard Russon <rich@flatcap.org>
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

#ifndef MUTT_PAGER_LINE_H
#define MUTT_PAGER_LINE_H

#include "mutt/lib.h"
#include "display.h"

typedef uint16_t LineFlags;                   ///< Flags for read_lines(), e.g. #MUTT_LF_HIDDEN
#define MUTT_LF_NO_FLAGS                   0  ///< No flags are set
#define MUTT_LF_HIDDEN              (1 <<  0) ///< XXX
#define MUTT_LF_QUOTED              (1 <<  1) ///< XXX
#define MUTT_LF_ATTACH              (1 <<  2) ///< XXX
#define MUTT_LF_PROCESSED           (1 <<  3) ///< XXX
#define MUTT_LF_RAW                 (1 <<  4) ///< XXX
#define MUTT_LF_HEADER              (1 <<  5) ///< XXX
#define MUTT_LF_HEADER_CONTINUATION (1 <<  6) ///< XXX
#define MUTT_LF_SIGNATURE           (1 <<  7) ///< XXX
#define MUTT_LF_BLANK               (1 <<  8) ///< XXX
#define MUTT_LF_ANSI                (1 <<  9) ///< XXX
#define MUTT_LF_CONTINUATION        (1 << 10) ///< XXX
#define MUTT_LF_TODO                (1 << 11) ///< XXX

/**
 * struct Line2 - A line of text in the pager
 */
struct Line2
{
  int offset;                      ///< XXX
  char *text;                      ///< XXX
  LineFlags flags;                 ///< XXX
  int color;                       ///< XXX
  struct TextSyntaxArray colors;   ///< XXX
  struct TextSyntaxArray searches; ///< XXX
};
ARRAY_HEAD(LineArray, struct Line2);

#endif /* MUTT_PAGER_LINE_H */
