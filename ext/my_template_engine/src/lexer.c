#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// Forward declarations for static helper functions
static void lexer_read_char(Lexer *l);
static char lexer_peek_char(const Lexer *l);
static Token new_token(TokenType type, const char *literal, int line);
static char *read_text(Lexer *l);
static char *read_identifier(Lexer *l);
static char *read_number(Lexer *l);
static char *read_string(Lexer *l);
static void skip_whitespace(Lexer *l);

Lexer *lexer_create(const char *input) {
    Lexer *l = (Lexer *)malloc(sizeof(Lexer));
    if (!l) return NULL;

    l->input = input;
    l->position = 0;
    l->readPosition = 0;
    l->ch = 0;
    l->line = 1;
    l->state = LEXER_STATE_TEXT;

    lexer_read_char(l); // Prime the lexer
    return l;
}

void lexer_destroy(Lexer *l) {
    if (l) {
        free(l);
    }
}

Token lexer_next_token(Lexer *l) {
    if (l->state == LEXER_STATE_TAG) {
        skip_whitespace(l);
    }

    // Handle tag endings first, as they switch the state back to TEXT
    if (l->ch == '}' || l->ch == '%') {
        if (l->state == LEXER_STATE_TAG) {
            if (l->ch == '}' && lexer_peek_char(l) == '}') {
                lexer_read_char(l); // consume '}'
                lexer_read_char(l); // consume '}'
                l->state = LEXER_STATE_TEXT;
                return new_token(TOKEN_VAR_END, "}}", l->line);
            }
            if (l->ch == '%' && lexer_peek_char(l) == '}') {
                lexer_read_char(l); // consume '%'
                lexer_read_char(l); // consume '}'
                l->state = LEXER_STATE_TEXT;
                return new_token(TOKEN_STMT_END, "%}", l->line);
            }
        }
    }
    if (l->ch == '#') {
        if (l->state == LEXER_STATE_TAG && lexer_peek_char(l) == '}') {
            lexer_read_char(l); // consume '#'
            lexer_read_char(l); // consume '}'
            l->state = LEXER_STATE_TEXT;
            return new_token(TOKEN_COMMENT_END, "#}", l->line);
        }
    }

    if (l->state == LEXER_STATE_TEXT) {
        char *text = read_text(l);
        if (strlen(text) > 0) {
            Token token = new_token(TOKEN_TEXT, text, l->line);
            free(text);
            return token;
        }
        free(text);
    }

    if (l->ch == '{') {
        if (lexer_peek_char(l) == '{') {
            lexer_read_char(l);
            lexer_read_char(l);
            l->state = LEXER_STATE_TAG;
            return new_token(TOKEN_VAR_START, "{{", l->line);
        }
        if (lexer_peek_char(l) == '%') {
            lexer_read_char(l);
            lexer_read_char(l);
            l->state = LEXER_STATE_TAG;
            return new_token(TOKEN_STMT_START, "{%", l->line);
        }
        if (lexer_peek_char(l) == '#') {
            lexer_read_char(l);
            lexer_read_char(l);
            l->state = LEXER_STATE_TAG;
            return new_token(TOKEN_COMMENT_START, "{#", l->line);
        }
    }

    if (l->state == LEXER_STATE_TAG) {
        if (isalpha(l->ch) || l->ch == '_') {
            char *ident = read_identifier(l);
            Token token = new_token(TOKEN_IDENTIFIER, ident, l->line);
            free(ident);
            return token;
        }
        if (isdigit(l->ch)) {
            char *num = read_number(l);
            Token token = new_token(TOKEN_NUMBER, num, l->line);
            free(num);
            return token;
        }
        if (l->ch == '"') {
            char *str = read_string(l);
            Token token = new_token(TOKEN_STRING, str, l->line);
            free(str);
            return token;
        }
    }

    if (l->ch == '\0') {
        return new_token(TOKEN_EOF, "", l->line);
    }

    char literal_str[2] = {l->ch, '\0'};
    Token token = new_token(TOKEN_ILLEGAL, literal_str, l->line);
    lexer_read_char(l);
    return token;
}

static void lexer_read_char(Lexer *l) {
    if (l->readPosition >= (int)strlen(l->input)) {
        l->ch = '\0';
    } else {
        l->ch = l->input[l->readPosition];
    }
    l->position = l->readPosition;
    l->readPosition++;
    if (l->ch == '\n') {
        l->line++;
    }
}

static char lexer_peek_char(const Lexer *l) {
    if (l->readPosition >= (int)strlen(l->input)) {
        return '\0';
    }
    return l->input[l->readPosition];
}

static Token new_token(TokenType type, const char *literal, int line) {
    Token tok;
    tok.type = type;
    tok.line = line;
    if (literal) {
        tok.literal = strdup(literal);
    } else {
        tok.literal = NULL;
    }
    return tok;
}

static void skip_whitespace(Lexer *l) {
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        lexer_read_char(l);
    }
}

static char *read_text(Lexer *l) {
    int start_pos = l->position;
    while (l->ch != '\0') {
        if (l->ch == '{') {
            char peek = lexer_peek_char(l);
            if (peek == '{' || peek == '%' || peek == '#') {
                break; // Start of a tag
            }
        }
        lexer_read_char(l);
    }

    int length = l->position - start_pos;
    char *text = (char *)malloc(length + 1);
    if (text) {
        strncpy(text, l->input + start_pos, length);
        text[length] = '\0';
    }
    return text;
}

static char *read_identifier(Lexer *l) {
    int start_pos = l->position;
    while (isalpha(l->ch) || isdigit(l->ch) || l->ch == '_') {
        lexer_read_char(l);
    }
    int length = l->position - start_pos;
    char *ident = (char *)malloc(length + 1);
    if (ident) {
        strncpy(ident, l->input + start_pos, length);
        ident[length] = '\0';
    }
    return ident;
}

static char *read_number(Lexer *l) {
    int start_pos = l->position;
    while (isdigit(l->ch)) {
        lexer_read_char(l);
    }
    int length = l->position - start_pos;
    char *num = (char *)malloc(length + 1);
    if (num) {
        strncpy(num, l->input + start_pos, length);
        num[length] = '\0';
    }
    return num;
}

static char *read_string(Lexer *l) {
    lexer_read_char(l); // Consume the opening "
    int start_pos = l->position;
    while (l->ch != '"' && l->ch != '\0') {
        lexer_read_char(l);
    }
    int length = l->position - start_pos;
    char *str = (char *)malloc(length + 1);
    if (str) {
        strncpy(str, l->input + start_pos, length);
        str[length] = '\0';
    }
    if (l->ch == '"') {
        lexer_read_char(l); // Consume the closing "
    }
    return str;
}
