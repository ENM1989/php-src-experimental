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
    const char *input = "{% for item in items %}{{ item.name }}{% endfor %}";
    Context *ctx = context_create();

    Context *item1_ctx = context_create();
    context_set_string(item1_ctx, "name", "a");

    Context *item2_ctx = context_create();
    context_set_string(item2_ctx, "name", "b");

    Context **items = (Context **)malloc(sizeof(Context*) * 2);
    items[0] = item1_ctx;
    items[1] = item2_ctx;

    context_set_list(ctx, "items", items, 2);

    Lexer *l = lexer_create(input);
    Parser *p = parser_create(l);
    RootNode *root = parse_template(p);
    char *output = render(root, ctx);

    ASSERT(strcmp(output, "ab") == 0);

    free(output);
    free_ast((Node*)root);
    parser_destroy(p);
    lexer_destroy(l);
    context_destroy(ctx);

    printf("For statement tests passed.\n");
    return 0;
}
