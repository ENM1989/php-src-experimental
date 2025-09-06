#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <string.h>
#include "context.h"

Context *context_create(void) {
    Context *ctx = (Context *)malloc(sizeof(Context));
    if (!ctx) return NULL;
    ctx->head = NULL;
    return ctx;
}

void context_destroy(Context *ctx) {
    if (!ctx) return;
    ContextItem *current = ctx->head;
    while (current) {
        ContextItem *next = current->next;
        free(current->key);
        if (current->type == CONTEXT_TYPE_STRING) {
            free(current->data.value);
        } else if (current->type == CONTEXT_TYPE_LIST) {
            for (int i = 0; i < current->data.list.count; i++) {
                // This is a shallow free, assumes items are managed elsewhere
            }
            free(current->data.list.items);
        }
        free(current);
        current = next;
    }
    free(ctx);
}

void context_set_string(Context *ctx, const char *key, const char *value) {
    ContextItem *item = (ContextItem *)malloc(sizeof(ContextItem));
    if (!item) return;
    item->key = strdup(key);
    item->type = CONTEXT_TYPE_STRING;
    item->data.value = strdup(value);
    item->next = ctx->head;
    ctx->head = item;
}

void context_set_list(Context *ctx, const char *key, ContextItem **items, int count) {
    ContextItem *item = (ContextItem *)malloc(sizeof(ContextItem));
    if (!item) return;
    item->key = strdup(key);
    item->type = CONTEXT_TYPE_LIST;
    item->data.list.items = items;
    item->data.list.count = count;
    item->next = ctx->head;
    ctx->head = item;
}

const ContextItem *context_get(const Context *ctx, const char *key) {
    ContextItem *current = ctx->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
