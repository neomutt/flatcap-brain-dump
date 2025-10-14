/**
 * struct ConfigInfo - Info about one config option
 */
struct ConfigInfo
{
  const char *name;  ///< Name of config option
  const char *value; ///< Value of config option
  const char *docs;  ///< One-liner docs for config option
};
ARRAY_HEAD(ConfigInfoArray, struct ConfigInfo);

