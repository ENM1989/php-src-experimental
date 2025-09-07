#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_fast_read.h"

#include <sys/stat.h>
#include <pthread.h>

// Data structure to pass to each thread
typedef struct {
    char *filepath;
    long offset;
    long chunk_size;
    char *buffer; // Pointer to the destination buffer section
    int error;
} thread_data_t;

// The worker function for each thread
static void *read_chunk_worker(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    data->error = 0;

    FILE *fp = fopen(data->filepath, "rb");
    if (!fp) {
        data->error = 1; // File open error
        return NULL;
    }

    // Seek to the specified offset
    if (fseek(fp, data->offset, SEEK_SET) != 0) {
        data->error = 2; // Seek error
        fclose(fp);
        return NULL;
    }

    // Read the chunk of data
    size_t read_bytes = fread(data->buffer, 1, data->chunk_size, fp);
    if (read_bytes != data->chunk_size) {
        data->error = 3; // Short read
    }

    fclose(fp);
    return NULL;
}

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_fast_read_file, 0)
    ZEND_ARG_ARRAY_INFO(0, "file_paths", 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ PHP_FUNCTION(fast_read_file)
 */
PHP_FUNCTION(fast_read_file)
{
    HashTable *file_paths_ht;
    zval *entry;
    zend_string *filepath_zs;

    // 1. Parse PHP arguments: expects one argument, an array.
    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_ARRAY_HT(file_paths_ht)
    ZEND_PARSE_PARAMETERS_END();

    int num_files = zend_hash_num_elements(file_paths_ht);
    if (num_files == 0) {
        php_error_docref(NULL, E_WARNING, "Input array of file paths cannot be empty");
        RETURN_FALSE;
    }

    // 2. Get file size from the first file in the array
    entry = zend_hash_index_find(file_paths_ht, 0);
    if (!entry || Z_TYPE_P(entry) != IS_STRING) {
         php_error_docref(NULL, E_WARNING, "Invalid file path found in array at index 0");
         RETURN_FALSE;
    }
    char *first_filepath = Z_STRVAL_P(entry);

    struct stat st;
    if (stat(first_filepath, &st) != 0) {
        php_error_docref(NULL, E_WARNING, "Could not stat file: %s", first_filepath);
        RETURN_FALSE;
    }
    long long total_size = st.st_size;
    if (total_size == 0) {
        RETURN_EMPTY_STRING();
    }

    // 3. Prepare for threading
    pthread_t *threads = ecalloc(num_files, sizeof(pthread_t));
    thread_data_t *thread_data = ecalloc(num_files, sizeof(thread_data_t));
    char *result_buffer = emalloc(total_size);

    long long chunk_size = total_size / num_files;
    long long current_offset = 0;
    int i = 0;

    // 4. Iterate through the array, create and start threads
    ZEND_HASH_FOREACH_VAL(file_paths_ht, entry)
        if (i >= num_files) break; // Should not happen, but for safety

        if (Z_TYPE_P(entry) != IS_STRING) {
            php_error_docref(NULL, E_WARNING, "Array must contain only string file paths");
            efree(threads);
            efree(thread_data);
            efree(result_buffer);
            RETURN_FALSE;
        }
        filepath_zs = Z_STR_P(entry);

        thread_data[i].filepath = ZSTR_VAL(filepath_zs);
        thread_data[i].offset = current_offset;

        // The last chunk might be larger if total_size is not divisible by num_files
        if (i == num_files - 1) {
            thread_data[i].chunk_size = total_size - current_offset;
        } else {
            thread_data[i].chunk_size = chunk_size;
        }

        thread_data[i].buffer = result_buffer + current_offset;
        thread_data[i].error = 0;

        if (pthread_create(&threads[i], NULL, read_chunk_worker, &thread_data[i]) != 0) {
            for (int j = 0; j < i; j++) {
                pthread_join(threads[j], NULL);
            }
            efree(threads);
            efree(thread_data);
            efree(result_buffer);
            php_error_docref(NULL, E_WARNING, "Failed to create thread %d", i);
            RETURN_FALSE;
        }

        current_offset += chunk_size;
        i++;
    ZEND_HASH_FOREACH_END();

    // 5. Join threads and check for errors
    int has_error = 0;
    for (i = 0; i < num_files; i++) {
        pthread_join(threads[i], NULL);
        if (thread_data[i].error) {
            has_error = 1;
            php_error_docref(NULL, E_WARNING, "Error reading from file: %s (error code: %d)", thread_data[i].filepath, thread_data[i].error);
        }
    }

    efree(threads);
    efree(thread_data);

    if (has_error) {
        efree(result_buffer);
        RETURN_FALSE;
    }

    // 6. Return the result as a PHP string
    RETURN_STRINGL(result_buffer, total_size);
    // result_buffer is automatically freed by Zend Engine
}
/* }}} */

/* {{{ fast_read_functions[]
 */
const zend_function_entry fast_read_functions[] = {
    PHP_FE(fast_read_file, arginfo_fast_read_file)
    PHP_FE_END
};
/* }}} */

/* {{{ fast_read_module_entry
 */
zend_module_entry fast_read_module_entry = {
    STANDARD_MODULE_HEADER,
    "fast_read",
    fast_read_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_FAST_READ_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FAST_READ
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(fast_read)
#endif
