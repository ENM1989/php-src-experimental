#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_cat.h"
#include "ext/standard/file.h"
#include "cat_arginfo.h"

PHP_FUNCTION(cat)
{
    char *filename;
    size_t filename_len;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &filename, &filename_len) == FAILURE) {
        return;
    }

    fp = fopen(filename, "r");
    if (!fp) {
        php_error_docref(NULL, E_WARNING, "Failed to open file: %s", filename);
        RETURN_FALSE;
    }

    array_init(return_value);

    while ((read = getline(&line, &len, fp)) != -1) {
        add_next_index_stringl(return_value, line, read);
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}

zend_module_entry cat_module_entry = {
    STANDARD_MODULE_HEADER,
    "cat",
    ext_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "1.0.0",
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_CAT
ZEND_GET_MODULE(cat)
#endif
