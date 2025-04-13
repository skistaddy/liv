#include "token.h"
#ifndef NODES_H
#define NODES_H


typedef struct {
    char* value;
    char* type;
} Identifier;

typedef struct {
    char* value;
} StringLiteral;

typedef struct {
    char* value;
} NumberLiteral;

typedef struct {
    struct Node **nodes;
} Group;

typedef struct {
    Group params;
    struct Node **body;
} ObjectLiteral;

typedef struct {
    Identifier name;
    struct Node *value;
} Declaration;

typedef struct Node {
    int kind;
    union {
        Identifier identifier;
        StringLiteral stringLiteral;
        NumberLiteral numberLiteral;
        ObjectLiteral objectLiteral;
        Group group;
        Declaration declaration;
    };
} Node;

#endif
