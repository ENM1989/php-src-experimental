#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "context.h"
#include "test_helpers.h"

int test_context() {
    Context *ctx = context_create();
    context_set(ctx, "name", "world");
    context_set(ctx, "animal", "dog");

    ASSERT(strcmp(context_get(ctx, "name"), "world") == 0);
    ASSERT(strcmp(context_get(ctx, "animal"), "dog") == 0);
    ASSERT(context_get(ctx, "cat") == NULL);

    context_destroy(ctx);

    printf("Context tests passed.\n");
    return 0;
}
