#include <stdlib.h>
#include "nodes.h"
#ifndef PARSER_H
#define PARSER_H

typedef struct {
    char* data;
    Token* tokens;
    size_t length;
    size_t index;
    Node** tree;
    size_t size;
} Parser;

Node* parseExpression(Parser* p);
Node* parseID(Parser* p);
Node* parseDeclaration(Parser* p, char* name);
GroupStruct parseGroup(Parser* p);
Node* parseObject(Parser* p, GroupStruct params);

Node** parse(char* data);

#endif
