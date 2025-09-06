#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "node.h"

typedef struct {
    Lexer *l;

    Token current_token;
    Token peek_token;
} Parser;

Parser *parser_create(Lexer *l);
void parser_destroy(Parser *p);

RootNode *parse_template(Parser *p);

#endif // PARSER_H
