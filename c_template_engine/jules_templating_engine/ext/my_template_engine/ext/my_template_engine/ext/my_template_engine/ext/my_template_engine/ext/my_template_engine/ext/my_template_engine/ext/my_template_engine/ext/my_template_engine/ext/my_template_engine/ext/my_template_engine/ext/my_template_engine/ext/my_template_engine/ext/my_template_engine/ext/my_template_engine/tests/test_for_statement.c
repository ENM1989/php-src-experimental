#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"
#include "parser.h"
#include "lexer.h"
#include "context.h"
#include "test_helpers.h"

int test_for_statement() {
    const char *input = "{% for item in items %}{{ item }}{% endfor %}";
    Context *ctx = context_create();
    char *items[] = {"a", "b", "c"};
    context_set_list(ctx, "items", items, 3);

    Lexer *l = lexer_create(input);
    Parser *p = parser_create(l);
    RootNode *root = parse_template(p);
    char *output = render(root, ctx);

    ASSERT(strcmp(output, "abc") == 0);

    free(output);
    free_ast((Node*)root);
    parser_destroy(p);
    lexer_destroy(l);
    context_destroy(ctx);

    printf("For statement tests passed.\n");
    return 0;
}
