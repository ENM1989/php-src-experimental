#ifndef CONTEXT_H
#define CONTEXT_H

// A single key-value pair in the context
typedef struct ContextItem {
    char *key;
    // For now, values are simple strings. This could be expanded to a variant type
    // to support numbers, booleans, arrays, etc.
    char *value;
    struct ContextItem *next;
} ContextItem;

// The context is a simple linked list of key-value pairs.
// A hash map would be more efficient for lookups, but this is sufficient for now.
typedef struct {
    ContextItem *head;
} Context;

// Function prototypes for creating and managing the context
Context *context_create(void);
void context_destroy(Context *ctx);
void context_set(Context *ctx, const char *key, const char *value);
const char *context_get(const Context *ctx, const char *key);

#endif // CONTEXT_H
