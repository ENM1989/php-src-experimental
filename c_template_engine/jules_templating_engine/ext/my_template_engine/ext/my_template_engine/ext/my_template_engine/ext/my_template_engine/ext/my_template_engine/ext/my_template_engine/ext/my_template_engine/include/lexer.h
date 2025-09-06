#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef enum {
    LEXER_STATE_TEXT,
    LEXER_STATE_TAG
} LexerState;

typedef struct {
    const char *input;
    int position;
    int readPosition;
    char ch;
    int line;
    LexerState state;
} Lexer;

Lexer *lexer_create(const char *input);
void lexer_destroy(Lexer *l);
Token lexer_next_token(Lexer *l);

#endif // LEXER_H
