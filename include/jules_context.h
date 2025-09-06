#ifndef JULES_CONTEXT_H
#define JULES_CONTEXT_H

// A single key-value pair in the context
typedef struct JulesContextItem {
    char *key;
    // For now, values are simple strings. This could be expanded to a variant type
    // to support numbers, booleans, arrays, etc.
    char *value;
    struct JulesContextItem *next;
} JulesContextItem;

// The context is a simple linked list of key-value pairs.
typedef struct {
    JulesContextItem *head;
} JulesContext;

// Function prototypes for creating and managing the context
JulesContext *jules_context_create(void);
void jules_context_destroy(JulesContext *ctx);
void jules_context_set(JulesContext *ctx, const char *key, const char *value);
const char *jules_context_get(const JulesContext *ctx, const char *key);

#endif // JULES_CONTEXT_H
