#include <stdlib.h>
#include "node.h"

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
