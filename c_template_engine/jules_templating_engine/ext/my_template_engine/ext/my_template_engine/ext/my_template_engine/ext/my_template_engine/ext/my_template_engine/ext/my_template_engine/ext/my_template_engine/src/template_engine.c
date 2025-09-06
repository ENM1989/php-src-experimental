#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <string.h>
#include "template_engine.h"
#include "lexer.h"
#include "parser.h"
#include "renderer.h"

void free_ast(Node *node);

char *template_render(const char *template_string, Context *ctx) {
    Lexer *l = lexer_create(template_string);
    Parser *p = parser_create(l);
    RootNode *root = parse_template(p);

    char *output = render(root, ctx);

    // free_ast is not yet implemented in a shared way
    // free_ast((Node *)root);
    parser_destroy(p);
    lexer_destroy(l);

    return output;
}
