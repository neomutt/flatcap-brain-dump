

struct BrowserItem
{
  struct BrowserItem children[];
  int num_children;
};


typedef bool (*br_key_cb)(struct Browser *b, int key);
typedef bool (*br_sort_cb)(struct Browser *b, int sort_id);

struct Browser
{
  struct BrowserItem items[];
  int num_items;
  int flags;
  br_key_cb kcb;
  br_sort_cb scb;
};

struct Sort
{
  const char *field;
  int sort_id;
}

struct Browser *br_create(void)
{
  // window*
  // flags
  // sorts
}

void br_destroy(struct Browser *b)
{
}

int br_select(struct Browser *b)
{
}

bool filebr_key_cb(struct Browser *b, int key)
{
  // BR_KEY_HANDLED
  // BR_KEY_NOT_HANDLED
}

bool br_sort_cb(struct Browser *b, 
