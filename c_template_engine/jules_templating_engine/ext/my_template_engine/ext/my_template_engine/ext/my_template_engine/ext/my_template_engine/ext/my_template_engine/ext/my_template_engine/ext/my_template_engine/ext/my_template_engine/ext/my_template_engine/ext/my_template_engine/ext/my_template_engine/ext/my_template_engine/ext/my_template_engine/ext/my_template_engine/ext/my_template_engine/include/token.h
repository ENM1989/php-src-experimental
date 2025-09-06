#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_TEXT,
    TOKEN_VAR_START,
    TOKEN_VAR_END,
    TOKEN_STMT_START,
    TOKEN_STMT_END,
    TOKEN_COMMENT_START,
    TOKEN_COMMENT_END,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_EOF,
    TOKEN_ILLEGAL,
    TOKEN_IN
} TokenType;

typedef struct {
    TokenType type;
    char *literal;
    int line;
} Token;

#endif // TOKEN_H
