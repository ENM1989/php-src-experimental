#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_colorize.h"
#include "colorize_arginfo.h"
#include <string.h>

PHP_FUNCTION(colorize)
{
    char *color;
    size_t color_len;
    char *text;
    size_t text_len;
    char *color_code = "";

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss", &color, &color_len, &text, &text_len) == FAILURE) {
        return;
    }

    if (strcmp(color, "black") == 0) {
        color_code = "\033[30m";
    } else if (strcmp(color, "red") == 0) {
        color_code = "\033[31m";
    } else if (strcmp(color, "green") == 0) {
        color_code = "\033[32m";
    } else if (strcmp(color, "yellow") == 0) {
        color_code = "\033[33m";
    } else if (strcmp(color, "blue") == 0) {
        color_code = "\033[34m";
    } else if (strcmp(color, "magenta") == 0) {
        color_code = "\033[35m";
    } else if (strcmp(color, "cyan") == 0) {
        color_code = "\033[36m";
    } else if (strcmp(color, "white") == 0) {
        color_code = "\033[37m";
    }

    php_printf("%s%s\033[0m", color_code, text);
}

zend_module_entry colorize_module_entry = {
    STANDARD_MODULE_HEADER,
    "colorize",
    ext_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "1.0.0",
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_COLORIZE
ZEND_GET_MODULE(colorize)
#endif
