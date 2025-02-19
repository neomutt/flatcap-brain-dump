/**
 * print_version_ansi - Print system and compile info to a file
 * @param fp       File to print to
 * @param use_ansi Use ANSI colour escape sequences
 * @retval true Text displayed
 *
 * Print information about the current system NeoMutt is running on.
 * Also print a list of all the compile-time information.
 */
bool print_version(FILE *fp, bool use_ansi)
{
  if (!fp)
    return false;

  struct utsname uts = { 0 };

  const char *col_cyan = "";
  const char *col_bold = "";
  const char *col_end = "";

  if (use_ansi)
  {
    col_cyan = "\033[1;36m"; // Escape, cyan
    col_bold = "\033[1m";    // Escape, bold
    col_end = "\033[0m";     // Escape, end
  }

  fprintf(fp, "%s%s%s\n", col_cyan, mutt_make_version(), col_end);
  fprintf(fp, "%s\n", _(Notice));

  uname(&uts);

  fprintf(fp, "%sSystem:%s ", col_bold, col_end);
#ifdef SCO
  fprintf(fp, "SCO %s", uts.release);
#else
  fprintf(fp, "%s %s", uts.sysname, uts.release);
#endif

  fprintf(fp, " (%s)", uts.machine);

  fprintf(fp, "\n%sncurses:%s %s", col_bold, col_end, curses_version());
#ifdef NCURSES_VERSION
  fprintf(fp, " (compiled with %s.%d)", NCURSES_VERSION, NCURSES_VERSION_PATCH);
#endif

#ifdef _LIBICONV_VERSION
  fprintf(fp, "\n%slibiconv:%s %d.%d", col_bold, col_end,
          _LIBICONV_VERSION >> 8, _LIBICONV_VERSION & 0xff);
#endif

#ifdef HAVE_LIBIDN
  fprintf(fp, "\n%slibidn2:%s %s", col_bold, col_end, mutt_idna_print_version());
#endif

#ifdef CRYPT_BACKEND_GPGME
  fprintf(fp, "\n%sGPGME:%s %s", col_bold, col_end, mutt_gpgme_print_version());
#endif

#ifdef USE_SSL_OPENSSL
#ifdef LIBRESSL_VERSION_TEXT
  fprintf(fp, "\n%sLibreSSL:%s %s", col_bold, col_end, LIBRESSL_VERSION_TEXT);
#endif
#ifdef OPENSSL_VERSION_TEXT
  fprintf(fp, "\n%sOpenSSL:%s %s", col_bold, col_end, OPENSSL_VERSION_TEXT);
#endif
#endif

#ifdef USE_SSL_GNUTLS
  fprintf(fp, "\n%sGnuTLS:%s %s", col_bold, col_end, GNUTLS_VERSION);
#endif

#ifdef HAVE_NOTMUCH
  fprintf(fp, "\n%slibnotmuch:%s %d.%d.%d", col_bold, col_end, LIBNOTMUCH_MAJOR_VERSION,
          LIBNOTMUCH_MINOR_VERSION, LIBNOTMUCH_MICRO_VERSION);
#endif

#ifdef HAVE_PCRE2
  {
    char version[24] = { 0 };
    pcre2_config(PCRE2_CONFIG_VERSION, version);
    fprintf(fp, "\n%sPCRE2:%s %s", col_bold, col_end, version);
  }
#endif

#ifdef USE_HCACHE
  const char *backends = store_backend_list();
  fprintf(fp, "\n%sstorage:%s %s", col_bold, col_end, backends);
  FREE(&backends);
#ifdef USE_HCACHE_COMPRESSION
  backends = compress_list();
  fprintf(fp, "\n%scompression:%s %s", col_bold, col_end, backends);
  FREE(&backends);
#endif
#endif

  rstrip_in_place((char *) configure_options);
  fprintf(fp, "\n\n%sConfigure options:%s %s\n", col_bold, col_end, (char *) configure_options);

  rstrip_in_place((char *) cc_cflags);
  fprintf(fp, "\n%sCompilation CFLAGS:%s %s\n", col_bold, col_end, (char *) cc_cflags);

  fprintf(fp, "\n%s%s%s\n", col_bold, _("Compile options:"), col_end);
  print_compile_options(CompOpts, fp);

  if (DebugOpts[0].name)
  {
    fprintf(fp, "\n%s%s%s\n", col_bold, _("Devel options:"), col_end);
    print_compile_options(DebugOpts, fp);
  }

  fprintf(fp, "\n");
#ifdef DOMAIN
  fprintf(fp, "DOMAIN=\"%s\"\n", DOMAIN);
#endif
#ifdef ISPELL
  fprintf(fp, "ISPELL=\"%s\"\n", ISPELL);
#endif
  fprintf(fp, "MAILPATH=\"%s\"\n", MAILPATH);
  fprintf(fp, "PKGDATADIR=\"%s\"\n", PKGDATADIR);
  fprintf(fp, "SENDMAIL=\"%s\"\n", SENDMAIL);
  fprintf(fp, "SYSCONFDIR=\"%s\"\n", SYSCONFDIR);

  fprintf(fp, "\n");
  fputs(_(ReachingUs), fp);

  fflush(fp);
  return !ferror(fp);
}
