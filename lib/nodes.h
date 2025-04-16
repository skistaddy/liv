#include <stdlib.h>
#include "token.h"
#ifndef NODES_H
#define NODES_H

typedef enum {
    IDNode,
    StringNode,
    NumberNode,
    GroupNode,
    ObjectNode,
    DeclarationNode
} NodeType;

typedef struct {
    char* value;
    char* type;
} IdentifierStruct;

typedef struct {
    char* value;
} StringStruct;

typedef struct {
    char* value;
} NumberStruct;

typedef struct {
    struct Node **nodes;
    size_t size;
} GroupStruct;

typedef struct {
    GroupStruct params;
    struct Node **body;
    size_t size;
} ObjectStruct;

typedef struct {
    IdentifierStruct name;
    struct Node *value;
} DeclarationStruct;

typedef struct Node {
    NodeType type;
    union {
        IdentifierStruct  Identifier;
        StringStruct      StringLiteral;
        NumberStruct      NumberLiteral;
        ObjectStruct      ObjectLiteral;
        GroupStruct       Group;
        DeclarationStruct Declaration;
    };
} Node;

#endif
