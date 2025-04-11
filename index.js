fs = require("fs")
path = require("path")
parser = require("./parser")
args = process.argv

if(args.length <= 2){
    console.log(args[1])
} else if(args[2] == "-h" || args[2] == "--help"){
    console.log("help")
} else {
    if(fs.existsSync(args[2])){
        output = new parser(fs.readFileSync(path.join(__dirname, args[2]), "utf8"))
        //console.log(output)
    }
}
