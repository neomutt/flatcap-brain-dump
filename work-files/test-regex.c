const char *text = "XXX\nabc\ndef\npqr\nXXX";
const char *str =
    // "abc$\n^def";
    // "abc$.^def";
    // "X[^\n]*X";
    "([a-z]+\n)+[a-z]+";
struct Regex *regex = mutt_regex_compile(str, 0);
regmatch_t matches[4] = { 0 };
bool b_match = mutt_regex_capture(regex, text, 4, matches);
printf("regex: >>%s<<\n", str);
printf("text: >>%s<<\n", text);
printf("match = %s\n", b_match ? "true" : "false");
printf("%d,%d\n", matches[0].rm_so, matches[0].rm_eo);
return 0;
