lexer = require("./lexer")
fs = require("fs")
path = require("path")

args = process.argv

if(args.length <= 2){
    console.log(args[1])
} else if(args[2] == "-h" || args[2] == "--help"){
    console.log("help")
} else {
    console.log(args[2])
    if(fs.existsSync(args[2])){
        output = lexer(fs.readFileSync(path.join(__dirname, args[2]), "utf8"))
        for(i in tokens){
            console.log(tokens[i].value)
        }
    }
}
