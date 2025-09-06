/* ext4 extension for PHP (c) 2025 Jules */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_ext4.h"
#include "ext4_arginfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

PHP_FUNCTION(ext4_defrag)
{
	char *path;
	size_t path_len;
	char command[1024];
	char real_path[MAXPATHLEN];
	int result;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_PATH(path, path_len)
	ZEND_PARSE_PARAMETERS_END();

	if (VCWD_REALPATH(path, real_path)) {
		if (access(real_path, F_OK) != -1) {
			snprintf(command, sizeof(command), "/usr/sbin/e4defrag %s > /dev/null 2>&1", real_path);
			result = system(command);

			if (result == 0) {
				RETURN_TRUE;
			}
		}
	}

	RETURN_FALSE;
}

PHP_FUNCTION(ext4_mount_options)
{
    char *device;
    size_t device_len;
    FILE *fp;
    char line[1024];
    char *found_device, *options_str;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(device, device_len)
    ZEND_PARSE_PARAMETERS_END();

    fp = fopen("/proc/mounts", "r");
    if (fp == NULL) {
        RETURN_FALSE;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        found_device = strtok(line, " ");
        if (found_device != NULL && strcmp(found_device, device) == 0) {
            strtok(NULL, " "); // mount_point
            strtok(NULL, " "); // fs_type
            options_str = strtok(NULL, " ");

            array_init(return_value);
            char *option = strtok(options_str, ",");
            while (option != NULL) {
                add_next_index_string(return_value, option);
                option = strtok(NULL, ",");
            }
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    RETURN_FALSE; // Device not found
}

PHP_FUNCTION(ext4_info)
{
    char *device;
    size_t device_len;
    FILE *fp;
    char command[1024];
    char line[1024];
    char *key, *value;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(device, device_len)
    ZEND_PARSE_PARAMETERS_END();

    snprintf(command, sizeof(command), "/usr/sbin/tune2fs -l %s 2>/dev/null", device);

    fp = popen(command, "r");
    if (fp == NULL) {
        RETURN_FALSE;
    }

    array_init(return_value);

    while (fgets(line, sizeof(line), fp) != NULL) {
        key = strtok(line, ":");
        value = strtok(NULL, "\n");

        if (key && value) {
            // Trim leading and trailing whitespace from key and value
            while (isspace((unsigned char)*key)) key++;
            char *end = value + strlen(value) - 1;
            while (end > value && isspace((unsigned char)*end)) end--;
            end[1] = '\0';
            while (isspace((unsigned char)*value)) value++;

            add_assoc_string(return_value, key, value);
        }
    }

    pclose(fp);
}

PHP_RINIT_FUNCTION(ext4)
{
#if defined(ZTS) && defined(COMPILE_DL_EXT4)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_MINFO_FUNCTION(ext4)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "ext4 support", "enabled");
	php_info_print_table_end();
}


zend_module_entry ext4_module_entry = {
	STANDARD_MODULE_HEADER,
	"ext4",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(ext4),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(ext4),			/* PHP_MINFO - Module info */
	PHP_EXT4_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_EXT4
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(ext4)
#endif
