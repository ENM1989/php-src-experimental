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
        free(current->value);
        free(current);
        current = next;
    }
    free(ctx);
}

void context_set(Context *ctx, const char *key, const char *value) {
    ContextItem *item = (ContextItem *)malloc(sizeof(ContextItem));
    if (!item) return;
    item->key = strdup(key);
    item->value = strdup(value);
    item->next = ctx->head;
    ctx->head = item;
}

const char *context_get(const Context *ctx, const char *key) {
    ContextItem *current = ctx->head;
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}
