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
   | Author: Jules <jules@upwork.com>                                     |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_grep.h"
#include "ext/pcre/php_pcre.h"
#include "php_streams.h"

PHP_FUNCTION(php_grep)
{
    char *pattern, *filename;
    size_t pattern_len, filename_len;
    php_stream *stream;
    char *line = NULL;
    size_t line_len;
    pcre2_code *re;
    PCRE2_UCHAR *pcre_pattern;
    int errorcode;
    PCRE2_SIZE erroroffset;
    pcre2_match_data *match_data;

    ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_STRING(pattern, pattern_len)
        Z_PARAM_STRING(filename, filename_len)
    ZEND_PARSE_PARAMETERS_END();

    pcre_pattern = (PCRE2_UCHAR *)pattern;
    re = pcre2_compile(pcre_pattern, pattern_len, 0, &errorcode, &erroroffset, NULL);

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errorcode, buffer, sizeof(buffer));
        php_error_docref(NULL, E_WARNING, "PCRE compilation failed: %s at offset %d", buffer, (int)erroroffset);
        RETURN_FALSE;
    }

    stream = php_stream_open_wrapper(filename, "r", 0, NULL);
    if (stream == NULL) {
        pcre2_code_free(re);
        php_error_docref(NULL, E_WARNING, "Failed to open file: %s", filename);
        RETURN_FALSE;
    }

    array_init(return_value);

    match_data = pcre2_match_data_create_from_pattern(re, NULL);
    while ((line = _php_stream_get_line(stream, NULL, 0, &line_len)) != NULL) {
        int rc;

        rc = pcre2_match(re, (PCRE2_UCHAR *)line, line_len, 0, 0, match_data, NULL);

        if (rc >= 0) {
            add_next_index_stringl(return_value, line, line_len);
        }
        efree(line);
    }

    pcre2_match_data_free(match_data);
    php_stream_close(stream);
    pcre2_code_free(re);
}
