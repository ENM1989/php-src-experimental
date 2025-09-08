/* elephant extension for PHP */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_elephant.h"
#include "elephant_arginfo.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

PHP_FUNCTION(elephant)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("    ___.-~\"~-._ __....\n");
	php_printf("    __\n");
	php_printf("    >.' ` \\ ~\"~ ``-.\n");
	php_printf("    >` _ ) `\\ `\\\n");
	php_printf("    >/` a)\n");
	php_printf("    >\n");
	php_printf("    >|\n");
	php_printf("    >`\\\n");
	php_printf("    >:``\n");
	php_printf("    >\n");
	php_printf("    >|\n");
	php_printf("    >\\\n");
	php_printf("    ><`-._|` .-. (\n");
	php_printf("    > .\n");
	php_printf("    >`;\\\\\n");
	php_printf("    >`-. `--'_.'-.;\\___' .\n");
	php_printf("    >.\n");
	php_printf("    >| \\\\\n");
	php_printf("    >_\n");
	php_printf("    >:--`\n");
	php_printf("    >|\n");
	php_printf("    >\n");
	php_printf("    >\n");
	php_printf("    >.' \\\\\n");
	php_printf("    >(\"\\ `/\n");
	php_printf("    >|\n");
	php_printf("    >'\n");
	php_printf("    >'\n");
	php_printf("    >\n");
	php_printf("    >:`;\n");
	php_printf("    >`\\'\\_`/\n");
	php_printf("    >.\\\n");
	php_printf("    >`~`=-.:\n");
	php_printf("    >\n");
	php_printf("    >``\n");
	php_printf("    >`._.'\n");
	php_printf("    >`\\\n");
	php_printf("    >|\n");
	php_printf("    >`\\\n");
	php_printf("    >(\n");
	php_printf("    > /\\ |\n");
	php_printf("    >`Y \\\n");
	php_printf("    >J Y |\n");
	php_printf("    >| `\\ \\ \n");
	php_printf("    > | | | \n");
	php_printf("    >| | | |\n");
	php_printf("    >\"---\" ___|\n");
	php_printf("    >___| /__|\n");
	php_printf("    >'\"\"\"\n");
	php_printf("    >'\"\"\" '\"\"\"\n");
}

PHP_RINIT_FUNCTION(elephant)
{
#if defined(ZTS) && defined(COMPILE_DL_ELEPHANT)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_MINFO_FUNCTION(elephant)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "elephant support", "enabled");
	php_info_print_table_end();
}

zend_module_entry elephant_module_entry = {
	STANDARD_MODULE_HEADER,
	"elephant",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(elephant),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(elephant),			/* PHP_MINFO - Module info */
	PHP_ELEPHANT_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_ELEPHANT
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(elephant)
#endif
