diff --git i/gui/curs_lib.c w/gui/curs_lib.c
index 4028b8ca0..c80e0b1d7 100644
--- i/gui/curs_lib.c
+++ w/gui/curs_lib.c
@@ -461,7 +461,8 @@ size_t mutt_strnwidth(const char *s, size_t n)
     return 0;
 
   wchar_t wc = 0;
-  int w;
+  int w = 0;
+  int w_last = 0;
   size_t k;
   mbstate_t mbstate = { 0 };
 
@@ -483,7 +484,12 @@ size_t mutt_strnwidth(const char *s, size_t n)
     }
     if (!IsWPrint(wc))
       wc = '?';
-    w += wcwidth(wc);
+
+    if ((wc == 0xfe0f) && (w_last == 1)) // Emoji variation
+      w++;
+
+    w_last = wcwidth(wc);
+    w += w_last;
   }
   return w;
 }
