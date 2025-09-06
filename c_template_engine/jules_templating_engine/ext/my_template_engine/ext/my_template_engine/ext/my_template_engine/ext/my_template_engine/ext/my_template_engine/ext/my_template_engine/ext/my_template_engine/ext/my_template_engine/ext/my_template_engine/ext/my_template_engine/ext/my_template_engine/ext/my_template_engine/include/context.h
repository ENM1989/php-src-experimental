#ifndef CONTEXT_H
#define CONTEXT_H

typedef enum {
    CONTEXT_TYPE_STRING,
    CONTEXT_TYPE_LIST
} ContextItemType;

typedef struct ContextItem {
    char *key;
    ContextItemType type;
    union {
        char *value;
        struct {
            struct ContextItem **items;
            int count;
        } list;
    } data;
    struct ContextItem *next;
} ContextItem;

typedef struct {
    ContextItem *head;
} Context;

Context *context_create(void);
void context_destroy(Context *ctx);
void context_set_string(Context *ctx, const char *key, const char *value);
void context_set_list(Context *ctx, const char *key, ContextItem **items, int count);
const ContextItem *context_get(const Context *ctx, const char *key);

#endif // CONTEXT_H
