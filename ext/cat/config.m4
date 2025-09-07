PHP_ARG_WITH([cat],
  [for cat support],
  [AS_HELP_STRING([--with-cat],
    [Include cat support])])

if test "$PHP_CAT" != "no"; then
  PHP_NEW_EXTENSION(cat, cat.c, $ext_shared)
fi
