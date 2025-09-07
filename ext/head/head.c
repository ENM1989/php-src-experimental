#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_head.h"
#include "ext/standard/file.h"
#include "head_arginfo.h"

PHP_FUNCTION(head)
{
    char *filename;
    size_t filename_len;
    zend_long lines = 10;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    zend_long i = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &filename, &filename_len, &lines) == FAILURE) {
        return;
    }

    fp = fopen(filename, "r");
    if (!fp) {
        php_error_docref(NULL, E_WARNING, "Failed to open file: %s", filename);
        RETURN_FALSE;
    }

    array_init(return_value);

    while ((read = getline(&line, &len, fp)) != -1) {
        if (i >= lines) {
            break;
        }
        add_next_index_stringl(return_value, line, read);
        i++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}

zend_module_entry head_module_entry = {
    STANDARD_MODULE_HEADER,
    "head",
    ext_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "1.0.0",
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_HEAD
ZEND_GET_MODULE(head)
#endif
