#ifndef CONTEXT_H
#define CONTEXT_H

typedef struct ContextItem {
    char *key;
    char *value;
    struct ContextItem *next;
} ContextItem;

typedef struct {
    ContextItem *head;
} Context;

Context *context_create(void);
void context_destroy(Context *ctx);
void context_set(Context *ctx, const char *key, const char *value);
const char *context_get(const Context *ctx, const char *key);

#endif // CONTEXT_H
