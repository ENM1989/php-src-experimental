/*
  +----------------------------------------------------------------------+
  | Copyright (c) The PHP Group                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | https://www.php.net/license/3_01.txt                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_parquet.h"

PHP_FUNCTION(parquet_test1)
{
    RETURN_STRING("This is a test");
}

PHP_MINIT_FUNCTION(parquet)
{
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(parquet)
{
    return SUCCESS;
}

PHP_RINIT_FUNCTION(parquet)
{
#if defined(ZTS) && defined(COMPILE_DL_PARQUET)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(parquet)
{
    return SUCCESS;
}

PHP_MINFO_FUNCTION(parquet)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "parquet support", "enabled");
    php_info_print_table_end();
}

zend_module_entry parquet_module_entry = {
    STANDARD_MODULE_HEADER,
    "parquet",
    NULL,
    PHP_MINIT(parquet),
    PHP_MSHUTDOWN(parquet),
    PHP_RINIT(parquet),
    PHP_RSHUTDOWN(parquet),
    PHP_MINFO(parquet),
    "0.0.1",
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PARQUET
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(parquet)
#endif
