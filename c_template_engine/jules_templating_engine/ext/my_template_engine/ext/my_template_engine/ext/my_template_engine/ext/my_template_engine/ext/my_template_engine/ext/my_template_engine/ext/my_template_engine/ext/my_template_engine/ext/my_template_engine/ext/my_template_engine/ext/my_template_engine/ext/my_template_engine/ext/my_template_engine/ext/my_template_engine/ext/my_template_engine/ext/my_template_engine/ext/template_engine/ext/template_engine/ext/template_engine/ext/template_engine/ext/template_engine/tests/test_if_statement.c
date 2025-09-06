#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"
#include "parser.h"
#include "lexer.h"
#include "context.h"
#include "test_helpers.h"

int test_if_statement() {
    const char *input1 = "{% if show %}Hello{% endif %}";
    Context *ctx1 = context_create();
    context_set_string(ctx1, "show", "true");
    Lexer *l1 = lexer_create(input1);
    Parser *p1 = parser_create(l1);
    RootNode *root1 = parse_template(p1);
    char *output1 = render(root1, ctx1);
    ASSERT(strcmp(output1, "Hello") == 0);
    free(output1);
    free_ast((Node*)root1);
    parser_destroy(p1);
    lexer_destroy(l1);
    context_destroy(ctx1);

    const char *input2 = "{% if show %}Hello{% else %}Goodbye{% endif %}";
    Context *ctx2 = context_create();
    context_set_string(ctx2, "show", "false");
    Lexer *l2 = lexer_create(input2);
    Parser *p2 = parser_create(l2);
    RootNode *root2 = parse_template(p2);
    char *output2 = render(root2, ctx2);
    ASSERT(strcmp(output2, "Goodbye") == 0);
    free(output2);
    free_ast((Node*)root2);
    parser_destroy(p2);
    lexer_destroy(l2);
    context_destroy(ctx2);

    printf("If statement tests passed.\n");
    return 0;
}
