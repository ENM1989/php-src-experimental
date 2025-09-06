#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "renderer.h"

// Simple dynamic string buffer
typedef struct {
    char *buffer;
    size_t length;
    size_t capacity;
} StringBuilder;

static void sb_init(StringBuilder *sb) {
    sb->buffer = (char *)malloc(128);
    sb->buffer[0] = '\0';
    sb->length = 0;
    sb->capacity = 128;
}

static void sb_append(StringBuilder *sb, const char *str) {
    if (!str) return;
    size_t str_len = strlen(str);
    if (sb->length + str_len >= sb->capacity) {
        size_t new_cap = sb->capacity * 2;
        if (new_cap < sb->length + str_len + 1) {
            new_cap = sb->length + str_len + 1;
        }
        sb->buffer = (char *)realloc(sb->buffer, new_cap);
        sb->capacity = new_cap;
    }
    strcat(sb->buffer, str);
    sb->length += str_len;
}

static char *sb_to_string(StringBuilder *sb) {
    return sb->buffer;
}

static void render_node(Node *node, Context *ctx, StringBuilder *sb);

char *render(RootNode *root, Context *ctx) {
    StringBuilder sb;
    sb_init(&sb);
    render_node((Node *)root, ctx, &sb);
    return sb_to_string(&sb);
}

static void render_node(Node *node, Context *ctx, StringBuilder *sb) {
    if (!node) return;

    switch (node->type) {
        case NODE_ROOT: {
            RootNode *root = (RootNode *)node;
            for (int i = 0; i < root->count; i++) {
                render_node(root->children[i], ctx, sb);
            }
            break;
        }
        case NODE_TEXT: {
            TextNode *text = (TextNode *)node;
            sb_append(sb, text->text);
            break;
        }
        case NODE_VARIABLE: {
            VariableNode *var = (VariableNode *)node;
            const char *value = context_get(ctx, var->name);
            if (value) {
                sb_append(sb, value);
            }
            break;
        }
        case NODE_IF_STATEMENT: {
            IfStatementNode *if_node = (IfStatementNode *)node;
            const char *value = context_get(ctx, if_node->condition);
            if (value && strcmp(value, "true") == 0) { // Simple truthiness check
                render_node((Node *)if_node->consequence, ctx, sb);
            } else if (if_node->alternative) {
                render_node((Node *)if_node->alternative, ctx, sb);
            }
            break;
        }
        default:
            break;
    }
}
