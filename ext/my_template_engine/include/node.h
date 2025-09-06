#ifndef NODE_H
#define NODE_H

#include "token.h"

typedef enum {
    NODE_ROOT,          // The root of the AST, contains a sequence of child nodes
    NODE_TEXT,          // A plain text block
    NODE_VARIABLE,      // A {{ ... }} expression to be rendered
    NODE_IF_STATEMENT,  // An if/else/endif block
    NODE_FOR_STATEMENT  // A for loop block
} NodeType;

// Base node structure that all other node types will embed
typedef struct Node {
    NodeType type;
} Node;

// The root node of the AST
typedef struct {
    Node base;
    Node **children;
    int count;
    int capacity;
} RootNode;

// Represents a block of plain text
typedef struct {
    Node base;
    char *text;
} TextNode;

// Represents a variable to be substituted, e.g., {{ name }}
typedef struct {
    Node base;
    char *name;
} VariableNode;

#endif // NODE_H
