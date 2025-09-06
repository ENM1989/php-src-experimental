#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main() {
    const char *input = "Hello, {{ name }}! This is a {# comment #} and a {% if condition %}statement{% endif %}.";
    Lexer *l = lexer_create(input);
    if (!l) {
        fprintf(stderr, "Failed to create lexer\n");
        return 1;
    }

    Token tok;
    do {
        tok = lexer_next_token(l);
        printf("Token { Type: %d, Literal: \"%s\", Line: %d, State: %d }\n", tok.type, tok.literal, tok.line, l->state);
        if (tok.literal) {
            free(tok.literal);
        }
    } while (tok.type != TOKEN_EOF);

    lexer_destroy(l);
    return 0;
}
