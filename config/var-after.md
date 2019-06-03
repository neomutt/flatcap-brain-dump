# NeoMutt Config Variables 2 - Simple Future

These are the changes I'd like to see in NeoMutt.
If you have any questions about them, please ask.

# Desired Features

* Easy transition to new code
* Independence from mutt code
* Testable
* Separation of types
* Extensible types
* Validation
* Notifications / listeners
* Scoped variables (allow inheritance)
* Scoped variables (fewer extern variables)
* Efficient variable lookups from strings
* Config backed by variables
* Subclassing of types (via validation)
* New syntax for scoped config

# Features of a Type

* Named
* Encapsulates one type of data
* Converts between type and string (in both directions)
* Set/Get functions for native type
* Reset function to revert to initial value
* Destructor to free resources

# Features of a Variable

* Name
* Type
* Pointer to a variable to store the value
* Initial value for the variable
* Validator function

# Examples

Here's how some of the types would work:

* Number
  - Stored as a `short`
  - Can be set using a numeric string
  - Displayed to user as a numeric string
  - Range-limited to size of a `short`
  - No resources to free

* Quad-Value
  - Stored as a `short`
  - User-facing strings: "no", "yes", "ask-no", "ask-yes"
  - Can be set using a string (from set)
  - Displayed to user as a string (from set)
  - No resources to free

* String
  - Stored as a `char *`
  - Set as a string
  - Displayed to user as a string
  - No validation
  - Resource freed when variable overwritten or destroyed

* Regex
  - Stored as a `struct Regex *`
    (Contains original string and compiled regex)
  - Set as a string
  - Displayed to user as a string
  - Validated as a correct regex
  - Resource freed when variable overwritten or destroyed

* Hcache Backend
  - Stored as a `short`
  - Set as a string
  - Displayed to user as a string
  - Validated against compile-time list
  - No resources to free

---

Rich / FlatCap
