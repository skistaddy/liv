#ifndef TOKEN_H
#define TOKEN_H

enum TokenType {
    String, Number,
    ID, Equals,
    LCurly, RCurly,
    LParen, RParen,
    LSquare, RSquare,
    Colon, Period,
    Op
};

typedef struct {
    enum TokenType type;
    char* value;
    int line;
    int col;
} Token;

#endif
