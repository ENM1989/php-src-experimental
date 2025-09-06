#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "node.h"
#include "test_helpers.h"

void free_ast(Node *node);

int test_parser() {
    const char *input = "Hello, {{ name }}!";
    Lexer *l = lexer_create(input);
    Parser *p = parser_create(l);
    RootNode *root = parse_template(p);

    ASSERT(root->base.type == NODE_ROOT);
    ASSERT(root->count == 3);

    TextNode *text1 = (TextNode *)root->children[0];
    ASSERT(text1->base.type == NODE_TEXT);
    ASSERT(strcmp(text1->text, "Hello, ") == 0);

    VariableNode *var1 = (VariableNode *)root->children[1];
    ASSERT(var1->base.type == NODE_VARIABLE);
    ASSERT(strcmp(var1->name, "name") == 0);

    TextNode *text2 = (TextNode *)root->children[2];
    ASSERT(text2->base.type == NODE_TEXT);
    ASSERT(strcmp(text2->text, "!") == 0);

    // free_ast is not yet implemented in a shared way
    // free_ast((Node *)root);
    parser_destroy(p);
    lexer_destroy(l);

    printf("Parser tests passed.\n");
    return 0;
}
