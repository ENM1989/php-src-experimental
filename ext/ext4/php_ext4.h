/* ext4 extension for PHP (c) 2025 Jules */

#ifndef PHP_EXT4_H
# define PHP_EXT4_H

extern zend_module_entry ext4_module_entry;
# define phpext_ext4_ptr &ext4_module_entry

# define PHP_EXT4_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_EXT4)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_EXT4_H */
