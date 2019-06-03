# NeoMutt Config Variables 1 - Current

This is the current state of the config items in NeoMutt.
If you have any questions about it, please ask.

# Config Items

Well over 400 config items of a mix of types.
Most simple, some backed by structs.

    180  DT_BOOL       boolean option 
    109  DT_STR        a string 
    38   DT_NUM        a number 
    34   DT_PATH       a pathname 
    28   DT_QUAD       quad-option (yes/no/ask-yes/ask-no) 
    24   DT_SYN        synonym for another variable 
    8    DT_RX         regular expressions
    6    DT_SORT       sorting methods 
    4    DT_MBCHARTBL  multibyte char table 
    2    DT_ADDR       e-mail address 
    1    DT_MAGIC      mailbox type 
    1    DT_HCACHE     header cache backend 

Centrally defined in `init.h`
    { name, type, flags, variable, initial_value }

Centrally backed by:
    variables in `global.h`
    booleans in `options.h`

# Config Usage

95% of the config items are only set when reading a config file (or the user
manually enters a command).  These are handled by `parse_set()`.  This
function notifies NeoMutt according to the flags defined in `init.h`.

All the config types need to be handled in `parse_set()` and any validation.

5% of the config items are set by the code, too.  These changes can occur
anywhere in the code and may need to send out notifications.

All the config items have a global scope.
This is why NeoMutt needs account- and folder-hooks.

# Pros of Current System

* Config strings are backed by real variables
* Easy access to variables
* Compact storage of booleans

# Cons of Current System

* Centralised => complex parsing routine
* No notifications mechanism
* No validation mechanism
* No scoping of variables
* Unsorted list of config items => ~200 `strcmp()`s for every lookup
* Not extendable, new types involve lots of code

---

Rich / FlatCap
