  const char *str1 = "❤xyz";
  const char *str2 = "❤️xyz";
  wchar_t *wstr = mutt_mem_calloc(1, 64);
  size_t len = 64;

  memset(wstr, 0, 64);
  mutt_mb_mbstowcs(&wstr, &len, 0, str1);
  len = wcswidth(wstr, 64);
  mutt_debug(LL_DEBUG1, "heart1: %ld >%s< [%ls]\n", len, str1, wstr);

  memset(wstr, 0, 64);
  mutt_mb_mbstowcs(&wstr, &len, 0, str2);
  len = wcswidth(wstr, 64);
  mutt_debug(LL_DEBUG1, "heart2: %ld >%s< [%ls]\n", len, str2, wstr);

