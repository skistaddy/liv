#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "lexer.h"

char* flow = "={}()[]:";
char* ops = "+!~%*&/-|^"; 
char* nums = "1234567890";

static int has(char* array, char seek){
    if(strchr(array, seek)) return 1;
    return 0;
}

static void init(Lexer* l, char* data){
    l->data = data;
    l->size = 0;
    l->tokens = malloc(sizeof(Token));
    l->index = 0;
    l->line = 1;
    l->col = 1;
    l->comment = 0;
    l->string = ' ';
    l->tok = malloc(1);
    l->tok[0] = '\0';
}

static void add(Lexer* l, char c){
    int length = strlen(l->tok);
    l->tok = realloc(l->tok, length + 2);
    l->tok[length] = c;
    l->tok[length + 1] = '\0';
}

static void reset(Lexer* l){
    l->tok = realloc(l->tok, 1);
    l->tok[0] = '\0';
}

static void consume(Lexer* l, enum TokenType type){
    if(l->tok != ' ' && l->tok != '\t' && strcmp(l->tok, "") != 0){
        l->size++;
        l->tokens = realloc(l->tokens, l->size * sizeof(Token));

        Token new = {type, strdup(l->tok), l->line, l->col};
        l->tokens[l->size - 1] = new;

        l->col += strlen(l->tok);
        reset(l);
    }
}

static void flowConsume(Lexer* l){
    switch(l->tok[0]){
        case '=':
            consume(l, Equals);
            break;
        case '{':
            consume(l, LCurly);
            break;
        case '}':
            consume(l, RCurly);
            break;
        case '(':
            consume(l, LParen);
            break;
        case ')':
            consume(l, RParen);
            break;
        case '[':
            consume(l, LSquare);
            break;
        case ']':
            consume(l, RSquare);
            break;
        case ':':
            consume(l, Colon);
            break;
    }
}

static void newline(Lexer* l){
    l->line++;
    l->col = 1;
    reset(l);
}

static char cur(Lexer* l){
    //printf("%c%d\n", l->data[l->index], l->index);
     return l->data[l->index];
}

static void next(Lexer* l){
    l->index++;
}

static void check(Lexer* l){
    char c = cur(l);

    if(l->comment){
        if(c == '\n'){
            newline(l);
            l->comment = 0;
        } else if(c == '#'){
            l->comment = 0;
        }
    } else if(l->string != ' '){
        if(c == l->string){
            l->string = ' ';
            consume(l, String);
            l->col++;
        } else {
            add(l, c);
        }
    } else if(c == ' '){
        consume(l, ID);
        l->col++;
    } else if(c == '#'){
        consume(l, ID);
        l->comment = 1;
    } else if(c == '"' || c == '\''){
        consume(l, ID);
        l->string = c;
        l->col++;
    } else if(c == '\n'){
        consume(l, ID);
        newline(l);
    } else if(has(flow, c)){
        consume(l, ID);
        reset(l);
        add(l, c);
        flowConsume(l);
    } else if(has(ops, c)){
        consume(l, ID);
        reset(l);
        add(l, c);
        consume(l, Op);
    } else {
        add(l, c);
    }
}

Lexer lex(char* data){
    Lexer l;
    init(&l, data);

    while(l.index < strlen(l.data)){
        check(&l);
        next(&l);
    }
    
    /*
    for(int i = 0; i < l.size; i++){
        printf("%s\n", l.tokens[i].value);
    }
    */

    return l;
}
