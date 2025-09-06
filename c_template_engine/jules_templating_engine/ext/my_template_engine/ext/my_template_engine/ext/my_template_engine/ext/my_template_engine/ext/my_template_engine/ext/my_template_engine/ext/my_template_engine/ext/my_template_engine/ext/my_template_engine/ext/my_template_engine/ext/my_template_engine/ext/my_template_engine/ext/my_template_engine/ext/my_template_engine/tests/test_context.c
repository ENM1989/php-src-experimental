#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"
#include "test_helpers.h"

int test_context() {
    Context *ctx = context_create();
    context_set_string(ctx, "name", "world");
    context_set_string(ctx, "animal", "dog");

    const ContextItem *item1 = context_get(ctx, "name");
    ASSERT(item1 && item1->type == CONTEXT_TYPE_STRING && strcmp(item1->data.value, "world") == 0);

    const ContextItem *item2 = context_get(ctx, "animal");
    ASSERT(item2 && item2->type == CONTEXT_TYPE_STRING && strcmp(item2->data.value, "dog") == 0);

    ASSERT(context_get(ctx, "cat") == NULL);

    context_destroy(ctx);

    printf("Context tests passed.\n");
    return 0;
}
