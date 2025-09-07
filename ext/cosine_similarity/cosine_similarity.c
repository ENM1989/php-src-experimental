/* cosine_similarity extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_cosine_similarity.h"
#include "cosine_similarity_arginfo.h"
#include <math.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

PHP_FUNCTION(cosine_similarity)
{
    zval *arr1, *arr2;
    HashTable *ht1, *ht2;
    zval *val1, *val2;
    double dot_product = 0.0;
    double magnitude1 = 0.0;
    double magnitude2 = 0.0;
    double similarity;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ARRAY(arr1)
        Z_PARAM_ARRAY(arr2)
    ZEND_PARSE_PARAMETERS_END();

    ht1 = Z_ARRVAL_P(arr1);
    ht2 = Z_ARRVAL_P(arr2);

    if (zend_hash_num_elements(ht1) != zend_hash_num_elements(ht2)) {
        zend_throw_error(NULL, "Arrays must have the same number of elements");
        RETURN_THROWS();
    }

    if (zend_hash_num_elements(ht1) == 0) {
        zend_throw_error(NULL, "Arrays cannot be empty");
        RETURN_THROWS();
    }

    zend_hash_internal_pointer_reset(ht1);
    zend_hash_internal_pointer_reset(ht2);

    while ((val1 = zend_hash_get_current_data(ht1)) != NULL &&
           (val2 = zend_hash_get_current_data(ht2)) != NULL) {
        convert_to_double(val1);
        convert_to_double(val2);

        dot_product += Z_DVAL_P(val1) * Z_DVAL_P(val2);
        magnitude1 += Z_DVAL_P(val1) * Z_DVAL_P(val1);
        magnitude2 += Z_DVAL_P(val2) * Z_DVAL_P(val2);

        zend_hash_move_forward(ht1);
        zend_hash_move_forward(ht2);
    }

    if (magnitude1 == 0.0 || magnitude2 == 0.0) {
        similarity = 0.0;
    } else {
        similarity = dot_product / (sqrt(magnitude1) * sqrt(magnitude2));
    }

    RETURN_DOUBLE(similarity);
}

PHP_RINIT_FUNCTION(cosine_similarity)
{
#if defined(ZTS) && defined(COMPILE_DL_COSINE_SIMILARITY)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_MINFO_FUNCTION(cosine_similarity)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "cosine_similarity support", "enabled");
	php_info_print_table_end();
}

zend_module_entry cosine_similarity_module_entry = {
	STANDARD_MODULE_HEADER,
	"cosine_similarity",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(cosine_similarity),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(cosine_similarity),			/* PHP_MINFO - Module info */
	PHP_COSINE_SIMILARITY_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_COSINE_SIMILARITY
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(cosine_similarity)
#endif
