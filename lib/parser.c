#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lexer.h"
#include "nodes.h"

static Token cur(Parser* p){
    return p->tokens[p->index];
}

static char* getLine(Parser* p){
    char* result = malloc(1);
    result[0] = '\0';

    int line = cur(p).line;
    int newlines = 0;
    int index = 0;
    size_t dataLength = strlen(p->data);

    while(index < dataLength){
        char c = p->data[index];
        size_t length = strlen(result);
        result = realloc(result, length + 2);
        result[length] = c;
        result[length + 1] = '\0';

        //printf("%s", result);

        index++;
        if(c == '\n'){
            newlines++;
            if(newlines == line){
                break;
            } else {
                free(result);
                result = malloc(1);
                result[0] = '\0';
            }
        }
    }

    return result;
}

static void error(Parser* p, char* msg){
    Token token = cur(p);

    char* spaces = malloc(token.col + 1);
    memset(spaces, ' ', token.col);
    spaces[token.col - 1] = '\0';

    printf("error: %s\n", msg);
    printf("%s", getLine(p)); // don't need newline bc of getLine
    printf("%s^ at %d:%d", spaces, token.line, token.col);
    exit(1);
}

static Token peek(Parser* p){
    if(p->index + 1 < p->length){
        return p->tokens[p->index + 1];
    } else {
        error(p, "unexpected end of file");
    }
}

static int notEOF(Parser* p){
    return (p->index < p->length);
}

static void next(Parser* p){
    if(notEOF(p)){
        p->index++;
    } else {
        p->index--;
        error(p, "unexpected end of file");
    }
}

static void init(Parser* p, char* data){
    Lexer l = lex(data);

    /*
    for (int i = 0; i < l.size; i++) {
        printf("Token[%d]: %s\n", i, l.tokens[i].value);
    }
    */

    p->data = data;
    p->tokens = l.tokens;
    p->length = l.size;
    p->index = 0;
    p->tree = NULL;
    p->size = 0;
}

static void push(Parser* p, Node* node){
    p->size++;
    p->tree = realloc(p->tree, p->size * sizeof(Node*));
    p->tree[p->size - 1] = node;
}

Node* parseExpression(Parser* p){
    printf("Token: %s at %d:%d\n", cur(p).value, cur(p).line, cur(p).col);
    Token c = cur(p);
    Node* id = malloc(sizeof(Node*));
    Node* node = malloc(sizeof(Node*));

    switch(c.type){
        case String:
            node->type = StringNode;
            node->StringLiteral.value = c.value;
            break;
        case Number:
            node->type = NumberNode;
            node->NumberLiteral.value = c.value;
            break;
        case ID:
            id = parseID(p);

            if(id->Identifier.type){
                node->Identifier.type = id->Identifier.type;
            }
            if(peek(p).type == Equals){
                next(p);
                next(p);
                node->type = DeclarationNode;
                node->Declaration.name = id->Identifier;
                next(p);
                node->Declaration.value = parseExpression(p);
            } else {
                node->Identifier.value = id->Identifier.value;
                node->type = IDNode;
            }
            break;
        case LParen:
            GroupStruct group = parseGroup(p);
            
            if(peek(p).type == LCurly){
                next(p);
                Node* object = parseObject(p, group);
                node = object;
            } else {
                node->type = GroupNode;
                node->Group.nodes = group.nodes;
            }
            break;
        case LCurly:
            GroupStruct params = {};
            node = parseObject(p, params);
            printf("outside obj");
            break;
        case Op:
            id = parseID(p);
            node->Identifier.value = id->Identifier.value;
            node->type = IDNode;
            break;
        default:
            char* type = malloc(sizeof c.type);
            sprintf(type, "%d", c.type);
            error(p, "unexpected token");
            break;
    }
    return node;
}

Node* parseID(Parser* p){
    Node* id = malloc(sizeof(Node*));
    id->Identifier.value = cur(p).value;

    if(peek(p).type == Colon){
        next(p);
        if(peek(p).type == ID){
            next(p);
            id->Identifier.type = cur(p).value;
        } else {
            next(p);
            error(p, "expected identifier");
        }
    } else {
        id->Identifier.type = NULL;
    }

    return id;
}

GroupStruct parseGroup(Parser* p){
    next(p);
    GroupStruct group;
    group.size = 0;
    group.nodes = NULL;

    while(notEOF(p) && cur(p).type != RParen){
        group.size++;
        group.nodes = realloc(
            group.nodes, 
            group.size * sizeof(Node)
        );
        group.nodes[group.size - 1] = parseExpression(p);
        next(p);
    }

    return group;
}

Node* parseObject(Parser* p, GroupStruct params){
    printf("inside obj");
    next(p);
    ObjectStruct obj = { 
        .size = 0, 
        .body = malloc(sizeof(Node)), 
        .params = params 
    };

    while(notEOF(p) && cur(p).type != RCurly){
        obj.size++;
        obj.body = realloc(
                obj.body, 
                obj.size * sizeof(Node*)
        );
        obj.body[obj.size - 1] = parseExpression(p);
        next(p);      
    }

    Node* node = malloc(sizeof(Node));
    node->type = ObjectNode;
    node->ObjectLiteral = obj;

    return node;
}

Node** parse(char *data){
    Parser p;
    init(&p, data);

    while(notEOF(&p)){
        Node* node = parseExpression(&p);
        push(&p, node);
        next(&p);
    }

    printf("finished parsing");

    return p.tree;  
}
