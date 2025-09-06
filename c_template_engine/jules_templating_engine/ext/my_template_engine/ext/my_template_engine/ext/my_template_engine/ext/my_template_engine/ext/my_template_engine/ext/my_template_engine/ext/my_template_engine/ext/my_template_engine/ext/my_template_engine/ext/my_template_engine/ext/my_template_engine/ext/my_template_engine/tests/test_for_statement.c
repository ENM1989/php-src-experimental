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
    ContextItem *item1 = (ContextItem *)malloc(sizeof(ContextItem));
    item1->key = strdup("item");
    item1->type = CONTEXT_TYPE_STRING;
    item1->data.value = strdup("a");

    ContextItem *item2 = (ContextItem *)malloc(sizeof(ContextItem));
    item2->key = strdup("item");
    item2->type = CONTEXT_TYPE_STRING;
    item2->data.value = strdup("b");

    ContextItem **items = (ContextItem **)malloc(sizeof(ContextItem *) * 2);
    items[0] = item1;
    items[1] = item2;

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
