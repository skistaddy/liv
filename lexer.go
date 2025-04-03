package main

import (
    "slices"
)

type Token struct {
    Type TokenType
    Value string
}

type TokenType int

const (
    ID TokenType = iota
    Flow
    Op
    Number
    String
)

func lex(data string) []Token {
    chars := []string{" ", "=", "{", "}", "(", ")", "[", "]", "\n"}
    ops := []string{"+", "!", "~", "%", "*", "&", "/", ":", "-", "|", "^"}
    numbers := []string{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}

    tokens := []Token{}
    tok := ""
    comment := false
    str := ' '
    
    consume := func(Type TokenType){
        number := true
        if tok == " " || tok == "\n" {
            tok = ""
        }
        for _, n := range tok {
            if !slices.Contains(numbers, string(n)){
                number = false
            }
        }
        if number { Type = Number }
        if len(tok) > 0 {
            tokens = append(tokens, Token{Type, tok})
            tok = ""
        }
    }

    for _, token := range data {
        st := string(token)

        if comment {
            if token == '\n' {
                comment = false
            } else if token == '#' {
                comment = false
            }
            tok = ""
        } else if token == '#' {
            consume(ID)
            comment = true
        } else if str != ' ' {
            tok += st
            if token == str {
                str = ' '
                consume(String)
            }
        } else if token == '"' || token == '\'' {
            consume(ID)
            str = token
            tok = st
        } else if slices.Contains(chars, st) {
            consume(ID)
            tok = st
            consume(Flow)
        } else if slices.Contains(ops, st) {       
            consume(ID)
            tok = st
            consume(Op)
        } else {
            tok += st
        }
    }

    consume(ID)

    return tokens
}
