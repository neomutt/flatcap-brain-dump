diff --git i/commands.c w/commands.c
index 35c8b424c..c1734b190 100644
--- i/commands.c
+++ w/commands.c
@@ -1705,6 +1705,13 @@ static enum CommandResult parse_version(struct Buffer *buf, struct Buffer *s,
   if (!StartupComplete)
     return MUTT_CMD_SUCCESS;
 
+  // colours:
+  // - bold - headers
+  // - cyan - version
+  // - red - disabled
+  // - green - enabled
+  // - cyan - devel
+
   struct PagedFile *pf = paged_file_new(NULL);
   print_version(pf, 0);
   dlg_spager(pf, "version", NeoMutt->sub);
diff --git i/version.c w/version.c
index fe1cb0ec3..95860c024 100644
--- i/version.c
+++ w/version.c
@@ -301,9 +301,10 @@ static const struct CompileOptions DebugOpts[] = {
 
 /**
  * print_compile_options - Print a list of enabled/disabled features
- * @param co    Array of compile options
- * @param width Width to wrap to (0 for no wrapping)
- * @param pf    PagedFile to write to
+ * @param co       Array of compile options
+ * @param width    Width to wrap to (0 for no wrapping)
+ * @param pf       PagedFile to write to
+ * @param use_ansi Use ANSI colour escape sequences
  *
  * Two lists are generated and passed to this function:
  *
@@ -314,13 +315,12 @@ static const struct CompileOptions DebugOpts[] = {
  * wrapped to SCREEN_WIDTH characters.
  */
 static void print_compile_options(const struct CompileOptions *co, int width,
-                                  struct PagedFile *pf)
+                                  struct PagedFile *pf, bool use_ansi)
 {
   if (!co || !pf)
     return;
 
   size_t used = 2;
-  bool tty = isatty(fileno(pf->fp));
   struct Buffer *buf = buf_pool_get();
   struct PagedLine *pl = NULL;
 
@@ -346,19 +346,19 @@ static void print_compile_options(const struct CompileOptions *co, int width,
     switch (co[i].enabled)
     {
       case 0: // Disabled
-        if (tty)
+        if (use_ansi)
           fmt = "\033[1;31m-%s\033[0m "; // Escape, red
         else
           fmt = "-%s ";
         break;
       case 1: // Enabled
-        if (tty)
+        if (use_ansi)
           fmt = "\033[1;32m+%s\033[0m "; // Escape, green
         else
           fmt = "+%s ";
         break;
       case 2: // Devel only
-        if (tty)
+        if (use_ansi)
           fmt = "\033[1;36m%s\033[0m "; // Escape, cyan
         else
           fmt = "%s ";
