class Identifier {
    constructor(value, type){
        this.value = value
        this.type = type
    }
}

class Group {
    constructor(...group){
        this.nodes = group
    }
}

class StringLiteral {
    constructor(value){
        this.value = value
    }
}

class NumberLiteral {
    constructor(value){
        this.value = value
    }
}

class ObjectLiteral {
    constructor(body, params){
        this.params = params
        this.body = body
    }
}

class Declaration {
    constructor(name, value){
        this.name = name
        this.value = value
    }
}

function parseID(p){
    id = new Identifier(p.cur.value)
    
    if(p.peek.type == ":"){
        p.next()
        id.type = p.expect("id").value
        p.next()
    }

    return id
}

function parseObject(p, params = []){
    p.next()
    body = []

    while(p.notEOF && p.cur.type != "}"){
        body.push(parseExpression(p))
        p.next()
    }

    return new ObjectLiteral(body, params)
}

function parseGroup(p){
    p.next()
    group = []

    while(p.notEOF && p.cur.type != ")"){
        group.push(parseExpression(p))
        p.next()
    }

    return new Group(...group)
}

function parseDeclaration(p, name){
    p.next()
    return new Declaration(name, parseExpression(p))
}

function parseExpression(p){
    switch(p.cur.type){
        case "string":
            value = p.cur.value
            return new StringLiteral(value)
        case "number":
            value = p.cur.value
            return new NumberLiteral(value)
        case "id":
            id = parseID(p)
            if(p.peek.type == "="){
                p.next()
                return parseDeclaration(p, id)
            } else {
                return id
            }
        case "(":
            group = parseGroup(p)
            if(p.peek.type == "{"){
                p.next()
                return parseObject(p, group.nodes)
            }
            return group
        case "{":
            return parseObject(p)
        case "op":
            return parseID(p)
        default:
            return p.err("unexpected token " + p.cur.type)
    }
}

function parse(p){
    while (p.notEOF) {
        node = parseExpression(p)
        p.tree.push(node)
        p.next()
    }
}

module.exports = parse
