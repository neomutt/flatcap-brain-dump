#include <stdio.h>
#include <time.h>

void dump_tm(struct tm *tm)
{
  printf("tm_year   = %d\n", tm->tm_year);
  printf("tm_mon    = %d\n", tm->tm_mon);
  printf("tm_mday   = %d\n", tm->tm_mday);
  printf("tm_hour   = %d\n", tm->tm_hour);
  printf("tm_min    = %d\n", tm->tm_min);
  printf("tm_sec    = %d\n", tm->tm_sec);

  // printf("tm_wday   = %d\n", tm->tm_wday);
  // printf("tm_yday   = %d\n", tm->tm_yday);
  // printf("tm_isdst  = %d\n", tm->tm_isdst);
  // printf("tm_gmtoff = %ld\n", tm->tm_gmtoff);
  // printf("tm_zone   = %s\n", tm->tm_zone);
  printf("\n");
}

int main()
{
  time_t t = time(NULL);
  struct tm tm = { 0 };

  gmtime_r(&t, &tm);
  dump_tm(&tm);

  // tm.tm_sec -= 7200;
  // tm.tm_min -= 120;
  tm.tm_mon -= 12;

  time_t t_mod = mktime(&tm);
  dump_tm(&tm);

  printf("old:  %ld\n", t);
  printf("new:  %ld\n", t_mod);
  printf("diff: %ld\n", t_mod - t);

  return 0;
}
