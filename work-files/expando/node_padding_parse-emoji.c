diff --git i/expando/node_padding.c w/expando/node_padding.c
index 65d74c6f6..717572fcd 100644
--- i/expando/node_padding.c
+++ w/expando/node_padding.c
@@ -333,6 +333,17 @@ struct ExpandoNode *node_padding_parse(const char *str, const char **parsed_unti
     assert(0 && "Unreachable");
   }
 
+  {
+    int c1 = mutt_mb_charlen(str, NULL);
+    if (c1 > 1)
+    {
+      const unsigned char *uc = (str + c1);
+      if ((uc[0] == 0xEF) && (uc[1] == 0xB8) && (uc[2] == 0x8F))
+        consumed += 3;
+    }
+    int c2 = mutt_mb_charlen(str + c1, NULL);
+  }
+
   *parsed_until = str + consumed;
   return node_padding_new(pt, str, str + consumed);
 }
