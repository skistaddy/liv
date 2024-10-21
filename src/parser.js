function parse(contents){
    ops = ["=", "(", ")", "{", "}", "[", "]", ",", "?", "`", ".", "+", "-", ">", "<"]
    whitespace = [" ", "", "\n", "\r"]
    tok = ""
    result = []
    foundString = false
    foundComment = false

    function add(x){
        if(x != "" && x != " " && x != "\n" && x != "\r"){
            result.push(x)
        }
    }

    for(i in contents){
        cur = contents[i]
        
        if(cur == "\""){
            if(foundComment){
                tok = ""
            } else if(foundString){
                add(tok + "\"")
                tok = ""
                foundString = false
            } else {
                add(tok)
                tok = "\""
                foundString = true
            }
        } else if (foundString){
            tok += cur
        } else if (cur == "#"){
            if(foundComment){
                foundComment = false
            } else {
                foundComment = true
            }
            tok = ""
        } else if(foundComment){
            if(cur == "\n" || cur == "\r"){
                foundComment = false
            }
            tok = ""
        } else if(ops.includes(cur)){
            add(tok)
            add(cur)
            tok = ""
        } else if(whitespace.includes(cur)){
            add(tok)
            tok = ""
        } else {
            tok += cur
        }
    }

    console.log(result)
}

module.exports = parse