// static
bool InHelp = false;
int braille_col = -1;
int braille_line = -1;
int TopLine = 0;
struct Email *OldEmail = NULL;
struct Resize *Resize = NULL;

// local
static char searchbuf[256] = { 0 };
char buf[1024];
int ch = 0, rc = -1;
bool first = true;
int searchctx = 0;
bool wrapped = false;
struct Menu *pager_menu = NULL;
int old_PagerIndexLines;
char *followup_to = NULL;
struct Mailbox *m = Context ? Context->mailbox : NULL;
int index_space = C_PagerIndexLines;
struct PagerRedrawData rd = { 0 };

// struct
struct PagerRedrawData
{
  PagerFlags flags;
  struct Pager *extra;
  int indexlen;
  int indicator; ///< the indicator line of the PI
  int oldtopline;
  int lines;
  int max_line;
  int last_line;
  int curline;
  int topline;
  bool force_redraw;
  int has_types;
  PagerFlags hide_quoted;
  int q_level;
  struct QClass *quote_list;
  LOFF_T last_pos;
  LOFF_T last_offset;
  struct Menu *menu; ///< the Pager Index (PI)
  regex_t search_re;
  bool search_compiled;
  PagerFlags search_flag;
  bool search_back;
  const char *banner;
  char *searchbuf;
  struct Line *line_info;
  FILE *fp;
  struct stat sb;
};

