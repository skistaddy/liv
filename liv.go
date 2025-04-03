package main

import (
    "fmt"
    "os"
)

func run(file string) (error, []Token) {
    data, err := os.ReadFile(file)
    if err != nil {
        fmt.Println(err)
        return err, nil
    }
    
    return nil, lex(string(data))
}

func Tprint(token Token) {
    fmt.Println(token.Type, token.Value)
}

func main(){
    if len(os.Args) == 1 {
        fmt.Println(os.Args[0])
    } else {
        switch os.Args[1]{
        case "-h":
        case "--help":
            fmt.Println("help")
        default:
            _, tokens := run(os.Args[1])
            for _, token := range tokens {
                Tprint(token)    
            }
        }
    }
}
