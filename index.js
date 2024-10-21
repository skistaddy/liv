fs = require("fs")
parse = require("./src/parser")

if(process.argv.length < 3){
    console.log("liv")
} else {
    file = process.argv[2]

    if(!fs.existsSync(file)){
        console.log(file + " does not exist")
        process.exit(1)
    } else if(fs.statSync(file).isDirectory()){
        console.log("please input a file")
        process.exit(1)
    } else {
        parse(fs.readFileSync(file, "utf8"))
    }
}