## Doxygen Headers - Exceptions for API functions

- `function_name - Description - Implements Api::function_name()`
- `function_name - Description - Wrapper for Api::function_name()`
- Don't document the parameters
- Only describe the function where it differs from the API
- Only document the retval if it differs from the API (or is constant)

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

