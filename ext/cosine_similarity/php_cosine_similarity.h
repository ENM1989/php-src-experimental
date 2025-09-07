/* cosine_similarity extension for PHP */

#ifndef PHP_COSINE_SIMILARITY_H
# define PHP_COSINE_SIMILARITY_H

extern zend_module_entry cosine_similarity_module_entry;
# define phpext_cosine_similarity_ptr &cosine_similarity_module_entry

# define PHP_COSINE_SIMILARITY_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_COSINE_SIMILARITY)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_COSINE_SIMILARITY_H */
