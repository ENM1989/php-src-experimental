#ifndef JULES_TOKEN_H
#define JULES_TOKEN_H

typedef enum {
    TOKEN_TEXT,         // Plain text
    TOKEN_VAR_START,    // {{
    TOKEN_VAR_END,      // }}
    TOKEN_STMT_START,   // {%
    TOKEN_STMT_END,     // %}
    TOKEN_COMMENT_START,// {#
    TOKEN_COMMENT_END,  // #}
    TOKEN_IDENTIFIER,   // variable names, keywords
    TOKEN_STRING,       // "a string"
    TOKEN_NUMBER,       // 123
    TOKEN_EOF,          // End of file/input
    TOKEN_ILLEGAL       // Illegal token
} JulesTokenType;

typedef struct {
    JulesTokenType type;
    char *literal;
    int line;
} JulesToken;

#endif // JULES_TOKEN_H
