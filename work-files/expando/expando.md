# Expandos

1. Define an Expando
2. Add Custom Parser
3. Define a Format String
4. Parse a Format String
5. Render a Format String

## Define an Expando

1. Short name
2. Long name
3. Type
4. Unique ID, named by domain
5. Flags

This is an example for `$index_format`:

```c
// ...
{ "a", "author",               EF_TYPE_STRING, EF_ENV_AUTHOR,           EF_FLAGS_NONE     },
{ "K", "mailing-list",         EF_TYPE_STRING, EF_ENV_MAILING_LIST,     EF_FLAGS_OPTIONAL },
{ "g", "tags",                 EF_TYPE_STRING, EF_EMAIL_TAGS,           EF_FLAGS_NONE     },
{ "l", "lines",                EF_TYPE_STRING, EF_EMAIL_LINES,          EF_FLAGS_OPTIONAL },
{ "c", "index-number",         EF_TYPE_NUMBER, EF_MV_INDEX_NUMBER,      EF_FLAGS_NONE     },
{ "M", "thread-number-hidden", EF_TYPE_NUMBER, EF_THREAD_NUMBER_HIDDEN, EF_FLAGS_OPTIONAL },
// ...
```

The UID is named for the data's domain, e.g. `ENV` for `struct Envelope`.
Defining the type, string vs number, will help simplify the callbacks later.
The long name can be left as `NULL` for now.

This should be enough information for the default parser to work with.
Including:
- Display of plain expandos
- printf style min/max widths
- printf style justification
- Conditional clauses

## Add Custom Parser

Some expandos need special handling:

- `%@...@` -- `index-format-hook`
- `%Gx` -- Notmuch tag transforms

It might also be useful to consider "dates" as custom.
They're used in quite a few places.

This is an example for `$index_format`:

```c
// ...
{ "@", NULL, EF_TYPE_STRING, EF_EMAIL_HOOK,          EF_FLAGS_NONE, ef_parser_index_format_hook },
{ "G", NULL, EF_TYPE_STRING, EF_EMAIL_NOTMUCH,       EF_FLAGS_NONE, ef_parser_notmuch_tags      },
{ "{", NULL, EF_TYPE_STRING, EF_EMAIL_DATE,          EF_FLAGS_NONE, ef_parser_date              },
{ "[", NULL, EF_TYPE_STRING, EF_EMAIL_DATE_LOCAL,    EF_FLAGS_NONE, ef_parser_date              },
{ "(", NULL, EF_TYPE_STRING, EF_EMAIL_DATE_RECEIVED, EF_FLAGS_NONE, ef_parser_date              },
// ...
```

**Notes**:
- Same format as above, with an extra parameter at the end
- Long name is empty

The custom parser will be given:
- String to parse
- Expando definition

It will return:
- A filled-in `ExpandoNode`
- Number of bytes consumed

## Define a Format String

Now that we've defined each expando, we can define some format strings.
The definition will live entirely within the config definition.

First the data:

```c
struct Expando IndexFormatData[] = {
// ...
{ "@", NULL,                   EF_TYPE_STRING, EF_EMAIL_HOOK,           EF_FLAGS_NONE,     ef_parser_index_format_hook },
{ "a", "author",               EF_TYPE_STRING, EF_ENV_AUTHOR,           EF_FLAGS_NONE,     NULL                        },
{ "c", "index-number",         EF_TYPE_NUMBER, EF_MV_INDEX_NUMBER,      EF_FLAGS_NONE,     NULL                        },
{ "g", "tags",                 EF_TYPE_STRING, EF_EMAIL_TAGS,           EF_FLAGS_NONE,     NULL                        },
{ "G", NULL,                   EF_TYPE_STRING, EF_EMAIL_NOTMUCH,        EF_FLAGS_NONE,     ef_parser_notmuch_tags      },
{ "K", "mailing-list",         EF_TYPE_STRING, EF_ENV_MAILING_LIST,     EF_FLAGS_OPTIONAL, NULL                        },
{ "l", "lines",                EF_TYPE_STRING, EF_EMAIL_LINES,          EF_FLAGS_OPTIONAL, NULL                        },
{ "M", "thread-number-hidden", EF_TYPE_NUMBER, EF_THREAD_NUMBER_HIDDEN, EF_FLAGS_OPTIONAL, NULL                        },
{ "(", NULL,                   EF_TYPE_STRING, EF_EMAIL_DATE_RECEIVED,  EF_FLAGS_NONE,     ef_parser_date              },
{ "[", NULL,                   EF_TYPE_STRING, EF_EMAIL_DATE_LOCAL,     EF_FLAGS_NONE,     ef_parser_date              },
{ "{", NULL,                   EF_TYPE_STRING, EF_EMAIL_DATE,           EF_FLAGS_NONE,     ef_parser_date              },
// ...
};
```

Then the config:

```c
static struct ConfigDef MainVars[] = {
// ...
{ "index_format", DT_EXPANDO|DT_NOT_EMPTY, IP "%4C %Z %{%b %d} %-15.15L (%<l?%4l&%4c>) %s", IndexFormatData, expando_validator,
  "printf-like format string for the index menu (emails)"
},
// ...
```

`expando_validator()` has enough information from the `ConfigDef` to validate the string.

## Parse a Format String

At startup, and when the user sets a value, the format string must be parsed.

```c
// ...
{ "a", "author",       EF_TYPE_STRING, EF_ENV_AUTHOR,      EF_FLAGS_NONE },
{ "g", "tags",         EF_TYPE_STRING, EF_EMAIL_TAGS,      EF_FLAGS_NONE },
{ "c", "index-number", EF_TYPE_NUMBER, EF_MV_INDEX_NUMBER, EF_FLAGS_NONE },
// ...
```

Using `Expando` array in `ConfigDef.data`, the parser checks each character.
When it finds a `%` it tries to find a matching Expando definition.

For simple expandos, the parser can do the work itself: parse any formatting,
then store the UID, type and flags in the `ExpandoNode`.

For custom expandos, the parser may need to try more than one callback to find a match.
The custom parser will return a completed `ExpandoNode` and the number of characters consumed.

When the parsing is successful, the resulting parse tree will be stored in `ConfigDef.var`

## Render a Format String

The final stage is to render a format string.

The renderer needs:
- Config variable (for the parse tree)
- Buffer for the results
- Max width
- Lots of data

A simple approach is to link the UID to a callback function:

```c
struct ExpandoCallbacks ec_data[] = {
// ...
{ EF_ENV_AUTHOR,           index_a },
{ EF_ENV_MAILING_LIST,     index_K },
{ EF_EMAIL_TAGS,           index_g },
{ EF_EMAIL_LINES,          index_l },
{ EF_MV_INDEX_NUMBER,      index_c },
{ EF_THREAD_NUMBER_HIDDEN, index_M },
// ...
};
```

The caller might look like:

```c
int rc = expando_render(buf, max_width, ec_data, callback_data);
```

The same `callback_data` will be given to every callback function.

Now, the render traverses the tree filling the buffer.
For each expando it lookup the UID and calls the callback function.

Currently, the callbacks do the formatting.
I think it'd be simpler if it just returned a string.

```c
const char *index_i(const struct ExpandoNode *self, intptr_t data)
{
  const struct HdrFormatInfo *hfi = (const struct HdrFormatInfo *) data;
  struct Email *email = hfi->email;

  if (email->env->message_id)
    return email->env->message_id;

  return "<no.id>";
}
```
