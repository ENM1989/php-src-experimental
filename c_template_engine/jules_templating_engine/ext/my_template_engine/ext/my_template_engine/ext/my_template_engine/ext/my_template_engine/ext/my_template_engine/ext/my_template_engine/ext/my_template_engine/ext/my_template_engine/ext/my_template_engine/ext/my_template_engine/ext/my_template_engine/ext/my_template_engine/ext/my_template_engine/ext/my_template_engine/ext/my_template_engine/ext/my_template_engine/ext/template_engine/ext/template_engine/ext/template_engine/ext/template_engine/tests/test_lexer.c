#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "test_helpers.h"

int test_lexer() {
    const char *input = "Hello, {{ name }}!";
    Lexer *l = lexer_create(input);

    Token t = lexer_next_token(l);
    ASSERT(t.type == TOKEN_TEXT && strcmp(t.literal, "Hello, ") == 0);
    free(t.literal);

    t = lexer_next_token(l);
    ASSERT(t.type == TOKEN_VAR_START);
    free(t.literal);

    t = lexer_next_token(l);
    ASSERT(t.type == TOKEN_IDENTIFIER && strcmp(t.literal, "name") == 0);
    free(t.literal);

    t = lexer_next_token(l);
    ASSERT(t.type == TOKEN_VAR_END);
    free(t.literal);

    t = lexer_next_token(l);
    ASSERT(t.type == TOKEN_TEXT && strcmp(t.literal, "!") == 0);
    free(t.literal);

    t = lexer_next_token(l);
    ASSERT(t.type == TOKEN_EOF);
    free(t.literal);

    lexer_destroy(l);
    printf("Lexer tests passed.\n");
    return 0;
}
