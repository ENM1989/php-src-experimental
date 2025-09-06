#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"
#include "parser.h"
#include "lexer.h"
#include "context.h"
#include "test_helpers.h"

int test_renderer() {
    const char *input = "Hello, {{ name }}!";
    Context *ctx = context_create();
    context_set(ctx, "name", "world");

    Lexer *l = lexer_create(input);
    Parser *p = parser_create(l);
    RootNode *root = parse_template(p);

    char *output = render(root, ctx);

    ASSERT(strcmp(output, "Hello, world!") == 0);

    free(output);
    // free_ast is not yet implemented in a shared way
    parser_destroy(p);
    lexer_destroy(l);
    context_destroy(ctx);

    printf("Renderer tests passed.\n");
    return 0;
}
