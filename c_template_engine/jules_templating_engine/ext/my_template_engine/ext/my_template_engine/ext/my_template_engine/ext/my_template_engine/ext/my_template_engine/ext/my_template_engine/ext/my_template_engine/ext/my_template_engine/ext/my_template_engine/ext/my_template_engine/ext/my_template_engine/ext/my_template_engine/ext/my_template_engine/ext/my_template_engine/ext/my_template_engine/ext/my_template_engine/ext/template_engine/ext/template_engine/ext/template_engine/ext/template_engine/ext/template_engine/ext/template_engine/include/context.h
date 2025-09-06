#ifndef CONTEXT_H
#define CONTEXT_H

typedef enum {
    CONTEXT_TYPE_STRING,
    CONTEXT_TYPE_LIST
} ContextItemType;

typedef struct {
    char **items;
    int count;
} ContextList;

typedef struct ContextItem {
    char *key;
    ContextItemType type;
    union {
        char *value;
        ContextList list;
    } data;
    struct ContextItem *next;
} ContextItem;

typedef struct Context {
    ContextItem *head;
} Context;

Context *context_create(void);
void context_destroy(Context *ctx);
void context_set_string(Context *ctx, const char *key, const char *value);
void context_set_list(Context *ctx, const char *key, char **items, int count);
const ContextItem *context_get(const Context *ctx, const char *key);
Context *context_clone(const Context *ctx);

#endif // CONTEXT_H
