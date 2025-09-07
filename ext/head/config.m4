PHP_ARG_WITH([head],
  [for head support],
  [AS_HELP_STRING([--with-head],
    [Include head support])])

if test "$PHP_HEAD" != "no"; then
  PHP_NEW_EXTENSION(head, head.c, $ext_shared)
fi
