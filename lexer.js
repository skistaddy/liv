class Token {
    constructor(t, v, l, c){
        this.type = t
        this.value = v
        this.line = l
        this.ch = c
    }
}

function lex(data){
    tokens = []
    line = 1
    ch = 1

    flow = ["=", "{", "}", "(", ")", "[", "]", ":"]
    ops = ["+", "!", "~", "%", "*", "&", "/", "-", "|", "^"]
    numbers = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]

    comment = false
    string = ""
    tok = ""

    newline = function(){
        line++
        ch = 1
        tok = ""
    }

    consume = function(type){
        number = true
        for (i in tok){
            if(!numbers.includes(tok[i])){
                number = false
            }
        }
        type = number ? "number" : type
        if (tok.length > 0){
            tokens.push(new Token(type, tok, line, ch))
        }
        ch += tok.length
        tok = ""
    }

    for(i in data){
        cur = data[i]
        if(comment){
            if(cur == "\n"){
                newline()
                comment = false
            } else if (cur == "#"){
                comment = false
            }
            ch++
            tok = ""
        } else if(string){
            if(cur == string){
                string = ""
                consume("string")
                ch++
            } else {
                tok += cur
            }
        } else if(cur == " "){
            consume("id")
            ch++
        } else if(cur == "#"){
            consume("id")
            comment = true
        } else if(cur == "\"" || cur == "'"){
            consume("id")
            string = cur
            ch++
        } else if(cur == "\n"){
            consume("id")
            newline()
        } else if(flow.includes(cur)){
            consume("id")
            tok = cur
            consume(cur)
        } else if(ops.includes(cur)){
            consume("id")
            tok = cur
            consume("op")
        } else {
            tok += cur
        }
    }
    consume("id")

    return tokens
}

module.exports = lex
