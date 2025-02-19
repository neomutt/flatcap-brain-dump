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

/**
 * @page pager_line XXX
 *
 * gcc -I. -o line pager/line.c libmutt.a libcore.a libemail.a libnotmuch.a libaddress.a libconfig.a libmutt.a -lpcre2-8 -lidn2
 */

#include "config.h"
#include <stdio.h>
#include "mutt/lib.h"
#include "line.h"

/**
 * free_lines - XXX
 */
void free_lines(struct LineArray *lines)
{
  if (!lines)
    return;

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    line->flags = MUTT_LF_NO_FLAGS;
    line->offset = 0;
    FREE(&line->text);
  }
}

/**
 * read_lines - XXX
 */
int read_lines(FILE *fp, struct LineArray *lines, int num_lines)
{
  if (!fp || !lines)
    return -1;

  int line_num = 0;
  size_t size = 0;

  for (int i = 0; i < num_lines; i++)
  {
    struct Line2 line = { 0 };

    line.text = mutt_file_read_line(NULL, &size, fp, &line_num, MUTT_RL_NO_FLAGS);
    if (!line.text)
      return i;

    if (line.text[0] == '\0')
    {
      FREE(&line.text);
      line.flags |= MUTT_LF_BLANK;
    }

    ARRAY_ADD(lines, line);
  }

  return ARRAY_SIZE(lines);
}

/**
 * grok_ansi - XXX
 */
int grok_ansi(const char *buf, int pos)
{
  int x = pos;

  while (isdigit(buf[x]) || (buf[x] == ';'))
    x++;

  pos = x;
  return pos;
}

/**
 * process_weed - XXX
 */
int process_weed(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  read_lines(fp, lines, 30);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & MUTT_LF_BLANK)
      break;

    line->flags |= MUTT_LF_HEADER;

    if ((line->text[0] == 'X') && (line->text[1] == '-'))
      line->flags |= MUTT_LF_HIDDEN;
    else if (isspace(line->text[0]))
      line->flags |= MUTT_LF_HEADER_CONTINUATION;
  }

  return 0;
}

/**
 * process_headers - XXX
 */
int process_headers(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  // read_lines(fp, lines, 20);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & MUTT_LF_BLANK)
      break;

    if (mutt_str_startswith(line->text, "From:") || mutt_str_startswith(line->text, "Subject:"))
      line->color = 136; // light cyan
    else
      line->color = 36; // dark cyan
  }

  return 0;
}

/**
 * process_attachments - XXX
 */
int process_attachments(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  // read_lines(fp, lines, 20);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & MUTT_LF_BLANK)
      break;

    // check_attachment_marker()
    // check_protected_header_marker()
    // line->color = 36;
    // line->flags |= MUTT_LF_ATTACH;
  }

  return 0;
}

/**
 * process_ansi - XXX
 */
int process_ansi(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  read_lines(fp, lines, 20);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & (MUTT_LF_HEADER | MUTT_LF_BLANK))
      continue;

    // for (int i = 0; i < 5; i++)
    // {
    //   char *esc = strchr(line->text, '\033'); // Escape
    //   if (!esc)
    //     continue;

    //   int pos0 = esc - line->text + 2;
    //   // printf("%d\n", line->text[pos0]);
    //   int pos = grok_ansi(line->text, pos0);
    //   if (pos == 0)
    //     continue;

    //   int len = mutt_str_len(line->text);
    //   memmove(esc, line->text + pos + 1, len - pos + 1);

    //   printf("%ld) ANSI %d, %d\n", ARRAY_FOREACH_IDX, pos0, pos);
    //   line->flags |= MUTT_LF_ANSI | MUTT_LF_PROCESSED;
    //   line->color = 135;
    // }
  }

  return 0;
}

/**
 * process_backspace - XXX
 */
int process_backspace(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  // read_lines(fp, lines, 20);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & (MUTT_LF_HEADER | MUTT_LF_BLANK))
      continue;

    for (int i = 0; i < 10; i++)
    {
      char *aitch = strchr(line->text, '\010'); // Ctrl-H
      if (!aitch)
        continue;

      if (aitch[-1] == aitch[1])
      {
        // bold
        line->color = 137;
      }
      else if (aitch[1] == '_')
      {
        // underline
        line->color = 133;
      }

      int len = mutt_str_len(line->text);
      int bytes = aitch - line->text;
      memmove(aitch, aitch + 2, len - bytes - 1);

      line->flags |= MUTT_LF_PROCESSED;
    }
  }

  return 0;
}

/**
 * process_quoted - XXX
 */
int process_quoted(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  // read_lines(fp, lines, 20);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & (MUTT_LF_HEADER | MUTT_LF_BLANK))
      continue;

    if (mutt_str_startswith(line->text, "> > > "))
    {
      line->flags |= MUTT_LF_QUOTED;
      line->color = 131;
    }
    else if (mutt_str_startswith(line->text, "> > "))
    {
      line->flags |= MUTT_LF_QUOTED;
      line->color = 132;
    }
    else if (mutt_str_startswith(line->text, "> "))
    {
      line->flags |= MUTT_LF_QUOTED;
      line->color = 134;
    }
  }

  return 0;
}

/**
 * process_signature - XXX
 */
int process_signature(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  // read_lines(fp, lines, 20);

  int sig_line = -1;
  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & (MUTT_LF_HEADER | MUTT_LF_BLANK))
      continue;

    if (mutt_str_startswith(line->text, "-- "))
    {
      sig_line = ARRAY_FOREACH_IDX;
      break;
    }
  }

  ARRAY_FOREACH_FROM(line, lines, sig_line)
  {
    if (line->flags & MUTT_LF_BLANK)
      break;

    line->color = 7;
  }

  return 0;
}

/**
 * process_color - XXX
 */
int process_color(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  // read_lines(fp, lines, 20);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & (MUTT_LF_HEADER | MUTT_LF_BLANK))
      continue;
  }

  return 0;
}

/**
 * process_search - XXX
 */
int process_search(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  // read_lines(fp, lines, 20);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & (MUTT_LF_HEADER | MUTT_LF_BLANK))
      continue;
  }

  return 0;
}

/**
 * process_wrap - XXX
 */
int process_wrap(struct LineArray *lines, FILE *fp)
{
  if (!lines)
    return -1;

  // read_lines(fp, lines, 20);

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & (MUTT_LF_HEADER | MUTT_LF_BLANK))
      continue;
  }

  return 0;
}

/**
 * dump_lines - XXX
 */
void dump_lines(struct LineArray *lines)
{
  if (!lines)
    return;

  struct Line2 *line = NULL;
  ARRAY_FOREACH(line, lines)
  {
    if (line->flags & MUTT_LF_HIDDEN)
      continue;

    if (line->color == 0)
    {
      printf("%2ld|%s\n", ARRAY_FOREACH_IDX, NONULL(line->text));
    }
    else
    {
      bool bright = (line->color > 100);
      int color = (line->color % 100);
      printf("%2ld|\033[%s%dm%s\033[0m\n", ARRAY_FOREACH_IDX,
             bright ? "1;" : "", color, NONULL(line->text));
    }
  }
}

/**
 * main - XXX
 */
int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  FILE *fp = NULL;
  fp = fopen(argv[1], "r");
  if (!fp)
  {
    printf("fopen: %s\n", argv[1]);
    return 1;
  }

  struct LineArray lines = ARRAY_HEAD_INITIALIZER;

  // process_decrypt()?
  // process_decode()?
  process_weed(&lines, fp);
  process_headers(&lines, fp);
  process_attachments(&lines, fp);
  process_ansi(&lines, fp);
  process_backspace(&lines, fp);
  process_quoted(&lines, fp);
  process_signature(&lines, fp);
  // process_url(&lines, fp); // ansi sequences for urls
  process_color(&lines, fp);
  process_search(&lines, fp);
  process_wrap(&lines, fp);

  dump_lines(&lines);
  free_lines(&lines);

  fclose(fp);
  return 0;
}
