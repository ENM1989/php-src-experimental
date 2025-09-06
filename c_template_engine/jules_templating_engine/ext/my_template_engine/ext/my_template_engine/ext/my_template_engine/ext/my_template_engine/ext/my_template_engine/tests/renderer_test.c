#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"
#include "parser.h"
#include "lexer.h"
#include "context.h"

int main() {
    const char *input = "Hello, {{ name }}!";
    Context *ctx = context_create();
    context_set(ctx, "name", "world");

    Lexer *l = lexer_create(input);
    Parser *p = parser_create(l);
    RootNode *root = parse_template(p);

    char *output = render(root, ctx);

    printf("Input: %s\n", input);
    printf("Output: %s\n", output);

    int result = 0;
    if (strcmp(output, "Hello, world!") != 0) {
        fprintf(stderr, "Render failed!\n");
        result = 1;
    }

    free(output);
    // free_ast is not needed here as the renderer does not free the ast
    parser_destroy(p);
    lexer_destroy(l);
    context_destroy(ctx);

    return result;
}
