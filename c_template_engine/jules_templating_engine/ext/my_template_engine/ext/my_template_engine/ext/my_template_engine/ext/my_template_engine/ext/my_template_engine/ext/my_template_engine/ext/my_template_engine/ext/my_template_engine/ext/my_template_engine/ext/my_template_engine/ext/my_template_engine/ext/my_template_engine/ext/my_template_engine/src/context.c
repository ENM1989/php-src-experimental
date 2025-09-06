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
                free(current->data.list.items[i]->key);
                free(current->data.list.items[i]->data.value);
                free(current->data.list.items[i]);
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

Context *context_clone(const Context *ctx) {
    Context *new_ctx = context_create();
    ContextItem *current = ctx->head;
    ContextItem *new_head = NULL;
    ContextItem *new_tail = NULL;

    while (current) {
        ContextItem *new_item = (ContextItem *)malloc(sizeof(ContextItem));
        new_item->key = strdup(current->key);
        new_item->type = current->type;
        if (current->type == CONTEXT_TYPE_STRING) {
            new_item->data.value = strdup(current->data.value);
        } else {
            // Deep copy of list would be needed for full functionality
            new_item->data.list.items = current->data.list.items;
            new_item->data.list.count = current->data.list.count;
        }
        new_item->next = NULL;

        if (!new_head) {
            new_head = new_item;
            new_tail = new_item;
        } else {
            new_tail->next = new_item;
            new_tail = new_item;
        }
        current = current->next;
    }
    new_ctx->head = new_head;
    return new_ctx;
}
