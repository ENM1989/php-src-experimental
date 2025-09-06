#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stdio.h>

#define ASSERT(condition) \
    if (!(condition)) { \
        fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #condition, __FILE__, __LINE__); \
        return 1; \
    }

#endif // TEST_HELPERS_H
