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
            const ContextItem *item = context_get(ctx, var->name);
            if (item && item->type == CONTEXT_TYPE_STRING) {
                sb_append(sb, item->data.value);
            }
            break;
        }
        case NODE_IF_STATEMENT: {
            IfStatementNode *if_node = (IfStatementNode *)node;
            const ContextItem *item = context_get(ctx, if_node->condition);
            if (item && item->type == CONTEXT_TYPE_STRING && strcmp(item->data.value, "true") == 0) {
                render_node((Node *)if_node->consequence, ctx, sb);
            } else if (if_node->alternative) {
                render_node((Node *)if_node->alternative, ctx, sb);
            }
            break;
        }
        case NODE_FOR_STATEMENT: {
            ForStatementNode *for_node = (ForStatementNode *)node;
            const ContextItem *item = context_get(ctx, for_node->collection_name);
            if (item && item->type == CONTEXT_TYPE_LIST) {
                for (int i = 0; i < item->data.list.count; i++) {
                    Context *loop_ctx = context_clone(ctx);

                    ContextItem *current_item = item->data.list.items[i]->head;
                    while(current_item) {
                        context_set_string(loop_ctx, current_item->key, current_item->data.value);
                        current_item = current_item->next;
                    }

                    render_node((Node *)for_node->body, loop_ctx, sb);
                    context_destroy(loop_ctx);
                }
            }
            break;
        }
        default:
            break;
    }
}
