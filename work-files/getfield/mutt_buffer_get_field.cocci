// This sample script expands a macro to call a function directly.
// It adds some default arguments.

@@
type T1;
identifier I1;
expression E1, E2, E3;
constant C1;
statement S1;
@@

(
T1 I1 =
- mutt_buffer_get_field(E1, E2, E3);
+ mutt_buffer_get_field_full(E1, E2, E3, false, NULL, NULL);
|
I1 =
- mutt_buffer_get_field(E1, E2, E3);
+ mutt_buffer_get_field_full(E1, E2, E3, false, NULL, NULL);
|
- mutt_buffer_get_field(E1, E2, E3);
+ mutt_buffer_get_field_full(E1, E2, E3, false, NULL, NULL);
|
- if (mutt_buffer_get_field(E1, E2, E3) == C1)
+ if (mutt_buffer_get_field_full(E1, E2, E3, false, NULL, NULL) == C1)
  { ... }
|
- if (mutt_buffer_get_field(E1, E2, E3) != C1)
+ if (mutt_buffer_get_field_full(E1, E2, E3, false, NULL, NULL) != C1)
  { ... }
)

