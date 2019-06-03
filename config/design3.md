New Config Design 3

---

Part 2 - Address

This takes a fictional Config item "$home_address"

NeoMutt defines the Address Type: DT_ADDR which is backed by a struct
Address pointer.

The 'foo' module registers its variable:

    { "home_address", DT_ADDR, &HomeAddr, "jim@example.com", NULL },

NeoMutt will set the HomeAddr Variable.

* 'home_address' has type DT_ADDR
* Lookup 'DT_ADDR' in the Type definitions
* Delegate parsing to the "Address" Type

Address Type:

* Allocate a new struct Address
* Parse the string into:
    - Real name
    - Email address

On success:
* Free the old value of HomeAddr
* Store the new value into HomeAddr
* Notify the Listeners

On failure:
* Free the temporary Address
* Notify the user

This variable doesn't have a validator function.

---

Part 2b - NULL

Some Types will allow an empty value to be set.
By default, NeoMutt stores empty strings as NULL.

Setting an Address Type to an empty string will release the old address and
set HomeAddr to NULL.

---

Rich / FlatCap
