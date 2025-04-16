#include "token.h"
#ifndef LEXER_H
#define LEXER_H

typedef struct {
    char* data;
    int index;
    Token* tokens;
    int size;
    int line;
    int col;
    int comment;
    char string;
    char* tok;
} Lexer;

Lexer lex(char* data);

#endif
