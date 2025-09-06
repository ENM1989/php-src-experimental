#ifndef NODE_H
#define NODE_H

#include "token.h"

typedef enum {
    NODE_ROOT,
    NODE_TEXT,
    NODE_VARIABLE,
    NODE_IF_STATEMENT,
    NODE_FOR_STATEMENT
} NodeType;

typedef struct Node {
    NodeType type;
} Node;

typedef struct {
    Node base;
    Node **children;
    int count;
    int capacity;
} RootNode;

typedef struct {
    Node base;
    char *text;
} TextNode;

typedef struct {
    Node base;
    char *name;
} VariableNode;

typedef struct {
    Node base;
    char *condition;
    RootNode *consequence;
    RootNode *alternative;
} IfStatementNode;

typedef struct {
    Node base;
    char *loop_var;
    char *collection_name;
    RootNode *body;
} ForStatementNode;

void free_ast(Node *node);

#endif // NODE_H
