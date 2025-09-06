#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "node.h"
#include "token.h"

static void parser_next_token(Parser *p);
static Node *parse_statement(Parser *p);
static TextNode *parse_text_node(Parser *p);
static VariableNode *parse_variable_node(Parser *p);

Parser *parser_create(Lexer *l) {
    Parser *p = (Parser *)malloc(sizeof(Parser));
    if (!p) return NULL;

    p->l = l;
    p->current_token.literal = NULL;
    p->peek_token.literal = NULL;
    parser_next_token(p);
    parser_next_token(p);
    return p;
}

void parser_destroy(Parser *p) {
    if (p) {
        if (p->current_token.literal) free(p->current_token.literal);
        if (p->peek_token.literal) free(p->peek_token.literal);
        free(p);
    }
}

static void parser_next_token(Parser *p) {
    if (p->current_token.literal) {
        free(p->current_token.literal);
    }
    p->current_token = p->peek_token;
    p->peek_token = lexer_next_token(p->l);
}

RootNode *parse_template(Parser *p) {
    RootNode *root = (RootNode *)malloc(sizeof(RootNode));
    root->base.type = NODE_ROOT;
    root->children = NULL;
    root->count = 0;
    root->capacity = 0;

    while (p->current_token.type != TOKEN_EOF) {
        Node *stmt = parse_statement(p);
        if (stmt) {
            if (root->count >= root->capacity) {
                root->capacity = root->capacity == 0 ? 8 : root->capacity * 2;
                root->children = (Node **)realloc(root->children, root->capacity * sizeof(Node *));
            }
            root->children[root->count++] = stmt;
        }
        parser_next_token(p);
    }

    return root;
}

static Node *parse_statement(Parser *p) {
    switch (p->current_token.type) {
        case TOKEN_TEXT:
            return (Node *)parse_text_node(p);
        case TOKEN_VAR_START:
            return (Node *)parse_variable_node(p);
        case TOKEN_COMMENT_START:
            while (p->current_token.type != TOKEN_COMMENT_END && p->current_token.type != TOKEN_EOF) {
                parser_next_token(p);
            }
            return NULL;
        case TOKEN_STMT_START:
             while (p->current_token.type != TOKEN_STMT_END && p->current_token.type != TOKEN_EOF) {
                parser_next_token(p);
            }
            return NULL;
        default:
            return NULL;
    }
}

static TextNode *parse_text_node(Parser *p) {
    TextNode *node = (TextNode *)malloc(sizeof(TextNode));
    node->base.type = NODE_TEXT;
    node->text = strdup(p->current_token.literal);
    return node;
}

static VariableNode *parse_variable_node(Parser *p) {
    parser_next_token(p);

    if (p->current_token.type != TOKEN_IDENTIFIER) {
        return NULL;
    }

    VariableNode *node = (VariableNode *)malloc(sizeof(VariableNode));
    node->base.type = NODE_VARIABLE;
    node->name = strdup(p->current_token.literal);

    parser_next_token(p);
    if (p->current_token.type != TOKEN_VAR_END) {
        free(node->name);
        free(node);
        return NULL;
    }

    return node;
}
