
struct EventColor
{
  struct UserColor *user_color;
  struct AttrColor *attr_color;
  const char       *pattern;
  int               match;
  bool              all;
};

color simple-object  attrs fg bg
color pattern-object attrs fg bg
color regex-object   attrs fg bg
	user_color OBJECT
	attr_color COLOUR
	pattern    NULL
	match      0
	all        false

color pattern-object attrs fg bg pattern
color regex-object   attrs fg bg regex
	user_color OBJECT
	attr_color COLOUR
	pattern    PATTERN
	match      0
	all        false

color regex-object   attrs fg bg regex num
	user_color OBJECT
	attr_color COLOUR
	pattern    PATTERN
	match      NUM
	all        false

uncolor *
	user_color NULL
	attr_color NULL
	pattern    NULL
	match      0
	all        true

uncolor simple-object
uncolor pattern-object
uncolor regex-object
	user_color OBJECT
	attr_color NULL
	pattern    NULL
	match      0
	all        false

uncolor pattern-object pattern
uncolor regex-object   regex
	user_color OBJECT
	attr_color NULL
	pattern    PATTERN
	match      0
	all        false

uncolor pattern-object *
uncolor regex-object   *
	user_color OBJECT
	attr_color NULL
	pattern    NULL
	match      0
	all        true

