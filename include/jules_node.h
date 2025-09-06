#ifndef JULES_NODE_H
#define JULES_NODE_H

#include "jules_token.h"

typedef enum {
    NODE_ROOT,          // The root of the AST, contains a sequence of child nodes
    NODE_TEXT,          // A plain text block
    NODE_VARIABLE,      // A {{ ... }} expression to be rendered
    NODE_IF_STATEMENT,  // An if/else/endif block
    NODE_FOR_STATEMENT  // A for loop block
} JulesNodeType;

// Base node structure that all other node types will embed
typedef struct JulesNode {
    JulesNodeType type;
} JulesNode;

// The root node of the AST
typedef struct {
    JulesNode base;
    JulesNode **children;
    int count;
    int capacity;
} JulesRootNode;

// Represents a block of plain text
typedef struct {
    JulesNode base;
    char *text;
} JulesTextNode;

// Represents a variable to be substituted, e.g., {{ name }}
typedef struct {
    JulesNode base;
    char *name;
} JulesVariableNode;

#endif // JULES_NODE_H
