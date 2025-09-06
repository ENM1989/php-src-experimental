#include <stdio.h>

int test_lexer();
int test_parser();
int test_renderer();
int test_context();
int test_if_statement();

int main() {
    int failed = 0;
    failed |= test_lexer();
    failed |= test_parser();
    failed |= test_renderer();
    failed |= test_context();
    failed |= test_if_statement();

    if (failed) {
        printf("Some tests failed.\n");
    } else {
        printf("All tests passed.\n");
    }

    return failed;
}
