#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "node.h"
#include "lexer.h"

// Helper function to print the AST
void print_ast(Node *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_ROOT: {
            RootNode *root = (RootNode *)node;
            printf("RootNode(count=%d):\n", root->count);
            for (int i = 0; i < root->count; i++) {
                print_ast(root->children[i]);
            }
            break;
        }
        case NODE_TEXT: {
            TextNode *text = (TextNode *)node;
            printf("  TextNode: \"%s\"\n", text->text);
            break;
        }
        case NODE_VARIABLE: {
            VariableNode *var = (VariableNode *)node;
            printf("  VariableNode: name=\"%s\"\n", var->name);
            break;
        }
        default:
            printf("  UnknownNode\n");
            break;
    }
}

// Helper function to free the AST
void free_ast(Node *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_ROOT: {
            RootNode *root = (RootNode *)node;
            for (int i = 0; i < root->count; i++) {
                free_ast(root->children[i]);
            }
            if (root->children) {
                free(root->children);
            }
            break;
        }
        case NODE_TEXT: {
            TextNode *text = (TextNode *)node;
            if (text->text) free(text->text);
            break;
        }
        case NODE_VARIABLE: {
            VariableNode *var = (VariableNode *)node;
            if (var->name) free(var->name);
            break;
        }
        default:
            break;
    }
    free(node);
}


int main() {
    const char *input = "Hello, {{ name }}!";
    Lexer *l = lexer_create(input);
    Parser *p = parser_create(l);

    RootNode *root = parse_template(p);

    printf("--- AST ---\n");
    print_ast((Node *)root);
    printf("-----------\n");

    // Cleanup
    free_ast((Node *)root);
    parser_destroy(p);
    lexer_destroy(l);

    return 0;
}
