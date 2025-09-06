#ifndef TEMPLATE_ENGINE_H
#define TEMPLATE_ENGINE_H

#include "context.h"

char *template_render(const char *template_string, Context *ctx);

#endif // TEMPLATE_ENGINE_H
