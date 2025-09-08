/* elephant extension for PHP */

#ifndef PHP_ELEPHANT_H
# define PHP_ELEPHANT_H

extern zend_module_entry elephant_module_entry;
# define phpext_elephant_ptr &elephant_module_entry

# define PHP_ELEPHANT_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_ELEPHANT)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_ELEPHANT_H */
