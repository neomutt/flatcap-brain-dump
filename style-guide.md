Style Guide
-----------

## Doxygen Headers - Exceptions for API functions

- `function_name - Description - Implements Api::function_name()`
- `function_name - Description - Wrapper for Api::function_name()`
- Don't document the parameters
- Only describe the function where it differs from the API
- Only document the retval if it differs from the API (or is constant)

## Variable naming

- Globals     are MixedCase
- #defines    are CAPITALISED
- functions   are snake_case
- structs     are MixedCase
- enums       are MixedCase
- enum-values are CAPITALISED
- locals      are lowercase

## Variable naming

- `struct Context *ctx`
- `FILE *fp`

- `struct Account *a` may have:
  - private data: `struct XyzAccountData *adata`
  - helper functions: `xyz_adata_free()`, `xyz_adata_get()`, `xyz_adata_new()`

- `struct Email *e` may have:
  - private data: `struct XyzEmailData *edata`
  - helper functions: `xyz_edata_free()`, `xyz_edata_get()`, `xyz_edata_new()`

- `struct Mailbox *m` may have:
  - private data: `struct XyzMailboxData *mdata`
  - helper functions: `xyz_mdata_free()`, `xyz_mdata_get()`, `xyz_mdata_new()`

## Function naming - APIs

- `OWNER_OBJECT_ACTION()` e.g. `imap_msg_open()`

## Buffer passing

- `(char *buf, size_t buflen)`

## Variable Use

- Define variables as late as possible (to reduce scope)
- e.g. `for (size_t i = 0; ...)`
- All pointers must be initialised (to `NULL`)
- Out-params to functions must be initialised before the call
  ```c
  int i = 0;
  perform(&i);
  ```

## Conditionals

- Pointers and bools may be tested with `!`
- Integer types must be tested against `0`

