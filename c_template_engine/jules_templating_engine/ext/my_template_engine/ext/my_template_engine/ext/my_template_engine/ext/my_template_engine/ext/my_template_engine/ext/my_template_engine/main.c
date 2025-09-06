#include <stdio.h>
#include <stdlib.h>
#include "template_engine.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"<template_string>\"\n", argv[0]);
        return 1;
    }

    const char *template = argv[1];

    Context *ctx = context_create();
    context_set(ctx, "name", "World");
    context_set(ctx, "adjective", "awesome");

    char *output = template_render(template, ctx);

    printf("Template: %s\n", template);
    printf("Output:   %s\n", output);

    free(output);
    context_destroy(ctx);

    return 0;
}
