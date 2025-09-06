#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// The lexer has two states: one for tokenizing plain text, and one for
// tokenizing content within template tags.
typedef enum {
    LEXER_STATE_TEXT, // Default state for tokenizing plain text
    LEXER_STATE_TAG   // State for tokenizing inside {{...}}, {%...%}, or {#...#}
} LexerState;

typedef struct {
    const char *input;
    int position;      // current position in input (points to current char)
    int readPosition;  // current reading position in input (after current char)
    char ch;           // current char under examination
    int line;          // current line number
    LexerState state;  // The current state of the lexer
} Lexer;

Lexer *lexer_create(const char *input);
void lexer_destroy(Lexer *l);
Token lexer_next_token(Lexer *l);

#endif // LEXER_H
