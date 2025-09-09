PHP_ARG_WITH([colorize],
  [for colorize support],
  [AS_HELP_STRING([--with-colorize],
    [Include colorize support])])

if test "$PHP_COLORIZE" != "no"; then
  PHP_NEW_EXTENSION(colorize, colorize.c, $ext_shared)
fi
