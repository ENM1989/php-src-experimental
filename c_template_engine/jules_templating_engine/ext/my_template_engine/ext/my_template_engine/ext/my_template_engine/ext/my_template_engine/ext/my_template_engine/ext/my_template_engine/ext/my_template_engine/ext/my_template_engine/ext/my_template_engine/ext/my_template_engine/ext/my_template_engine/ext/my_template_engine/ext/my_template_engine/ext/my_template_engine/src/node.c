#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <string.h>
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
        case NODE_IF_STATEMENT: {
            IfStatementNode *if_node = (IfStatementNode *)node;
            if (if_node->condition) free(if_node->condition);
            if (if_node->consequence) free_ast((Node *)if_node->consequence);
            if (if_node->alternative) free_ast((Node *)if_node->alternative);
            break;
        }
        case NODE_FOR_STATEMENT: {
            ForStatementNode *for_node = (ForStatementNode *)node;
            if (for_node->loop_var) free(for_node->loop_var);
            if (for_node->collection_name) free(for_node->collection_name);
            if (for_node->body) free_ast((Node *)for_node->body);
            break;
        }
        default:
            break;
    }
    free(node);
}
