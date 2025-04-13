lexer = require("./lexer")
parse = require("./parserFuncs")


class Parser {
    constructor(data){
        this.data = data
        this.tokens = lexer(data)
        this.index = 0
        this.tree = []

        parse(this)
    }

    get cur(){
        return this.tokens[this.index]
    }

    get peek(){
        if(this.index + 1 < this.tokens.length){
            return this.tokens[this.index + 1]
        } else {
            return { type: "" }
        }
    }

    get notEOF(){
        return this.index < this.tokens.length
    }

    next(){
        if(this.notEOF){
            this.index++
        } else {
            this.index--
            this.err("unexpected end of file")
        }
    }

    expect(...types){
        let token = this.peek

        if(!types.includes(token.type)) { 
            this.next()
            this.err("unexpected token" + token.type) 
        }
        return token
    }

    err(msg){
        let token = this.cur
        console.log("error:", msg)
        console.log(
            this.data.split("\n")[token.line - 1]
        )
        console.log(
            Array(token.ch - 1).fill(" ").join("") 
            + "^ at"
            ,token.line 
            + ":" 
            + token.ch
        )
        process.exit(1)
    }
}

module.exports = Parser
