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
                context_destroy(current->data.list.items[i]);
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

void context_set_list(Context *ctx, const char *key, Context **items, int count) {
    ContextItem *item = (ContextItem *)malloc(sizeof(ContextItem));
    if (!item) return;
    item->key = strdup(key);
    item->type = CONTEXT_TYPE_LIST;
    item->data.list.items = (struct Context **)malloc(sizeof(struct Context*) * count);
    for (int i = 0; i < count; i++) {
        item->data.list.items[i] = context_clone(items[i]);
    }
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
    if (!ctx) return new_ctx;

    ContextItem *current = ctx->head;
    ContextItem **new_current_ptr = &new_ctx->head;

    while (current) {
        ContextItem *new_item = (ContextItem *)malloc(sizeof(ContextItem));
        new_item->key = strdup(current->key);
        new_item->type = current->type;
        if (current->type == CONTEXT_TYPE_STRING) {
            new_item->data.value = strdup(current->data.value);
        } else {
            new_item->data.list.count = current->data.list.count;
            new_item->data.list.items = (struct Context **)malloc(sizeof(struct Context*) * new_item->data.list.count);
            for (int i = 0; i < new_item->data.list.count; i++) {
                new_item->data.list.items[i] = context_clone(current->data.list.items[i]);
            }
        }
        new_item->next = NULL;
        *new_current_ptr = new_item;
        new_current_ptr = &new_item->next;
        current = current->next;
    }
    return new_ctx;
}
