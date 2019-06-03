New Config Design 2

aka A Day in the Life of a Config Item

---

Part 1 - Number

This takes a fictional Config item "$foo_percentage"

NeoMutt defines the Number Type: DT_NUM which is backed by a short int.

The 'foo' module registers its variable:

    { "foo_percentage", DT_NUM, &FooPct, 42, foo_pct_validator },

NeoMutt will set the FooPct Variable (explanation below).
Note: The initial value is Type-specific.

and a listener:

    bool foo_config_event(ConfigSet *cs, HashElem *he, char *name, ConfigEvent ev);

Now we read the config file:
    set foo_percentage = 96   # Dangerously high

* mutt_parse_rc_line() identifies the 'set' command
* parse_set() splits the line into
    - 'foo_percentage' variable
    - the assignment '='
    - the value string '96'
* Lookup 'foo_percentage' in the ConfigSet
    - It has type DT_NUM
* Lookup 'DT_NUM' in the Type definitions
* Delegate parsing to the "Number" Type

The "Number" Type has a 'setter' function to convert a string to data.
If any of the steps fail, the user will be notified and the Variable won't be
changed.

* Convert the string to an integer
* Check the range of the integer (we store our value in a short)
    - Is it less than SHRT_MIN?
    - It is greater than SHRT_MAX?

Validator:

This variable has a validator function, which is now called.
In this case, it checks that the value is in the range 0-100.
If it's not, it returns false and an error message.

If the validator succeeds, then the Variable is set to the new value.
Finally, the ConfigSet sends out a notification to all the Listeners.

    foo_config_event() is called

---

Rich / FlatCap
