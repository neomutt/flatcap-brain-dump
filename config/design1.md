New Config Design 1

Key:
    Account     Private subset of a ConfigSet
    Config      User-settable variable, e.g. "$index_format"
    ConfigSet   Collection of Config items
    Event       A change to the ConfigSet, e.g. Config item set
    Hash        HashTable data structure
    HashEntry   Item in HashTable
    Listener    Function called when an event happens
    Type        One kind of Config/Variable, e.g. Number
    Variable    Store for a Config

---

Configuration begins with the ConfigSet.  It contains:
* Hash Table to store the Configs
* Set of registered Types
* Set of Listeners

First we create a ConfigSet and register some Types.  Each Type is
responsible for one data type.  Each Type has:
* name              Human-readable name
* setter/getter     Set/get the variable as a string
* nsetter/ngetter   Setter/getter as a native type, e.g. struct Address
* resetter          Reset variable to factory settings
* destructor        Release the resources

NeoMutt's basic Types are:
* Address
* Bool
* Magic
* MbCharTable
* Number
* Path
* Quad
* Regex
* Sort
* String

Now we register some Variables.  Each is represented by a VariableDef which
is similar to the format in `mutt_config.c`

    /* Name            Type     Variable      Initial      Validator */
    { "timeout",       DT_NUM,  &Timeout,     600,         NULL },
    { "recall",        DT_QUAD, &OPT_RECALL,  MUTT_ASKYES, NULL },
    { "print_command", DT_PATH, &PrintCmd,    IP "lpr",    NULL },

Finally, we can register some Listeners.  These functions are called
whenever a Config is set (either by the user, or in the code).

---

Rich / FlatCap
