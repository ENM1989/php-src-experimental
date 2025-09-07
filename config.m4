PHP_ARG_ENABLE(fast_read, whether to enable fast_read support,
[ --enable-fast_read   Enable fast_read support])

if test "$PHP_FAST_READ" = "yes"; then
  PHP_ADD_LIBRARY(pthread, 1, FAST_READ_SHARED_LIBADD)
  AC_DEFINE(HAVE_FAST_READ, 1, "Whether to enable fast_read support")
  PHP_NEW_EXTENSION(fast_read, fast_read.c, $ext_shared)
fi
