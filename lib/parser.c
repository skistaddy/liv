#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "nodes.h"

typedef struct {
    char* data;
    Token* tokens;
    int size;
    int index;
    Node* tree;
} Parser;

void initParser(Parser* p, char* data){
    p->data = data;
    p->tokens = lex(data);
    p->size = 0;
    p->index = 0;
    p->tree = malloc(sizeof(Node));
}

Node* parse(char *data){
    Parser p;
    initParser(&p, data);

    return p.tree;  
}
