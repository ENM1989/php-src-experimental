#ifndef PHP_FAST_READ_H
#define PHP_FAST_READ_H

extern zend_module_entry fast_read_module_entry;
#define phpext_fast_read_ptr &fast_read_module_entry

#define PHP_FAST_READ_VERSION "0.1.0"

#if defined(ZTS) && defined(COMPILE_DL_FAST_READ)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_FAST_READ_H */
