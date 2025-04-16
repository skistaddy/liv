#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/parser.h"

char* readfile(char* filename){
    FILE* file = fopen(filename, "r");

    if(!file){
        printf("'%s' does not exist", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(length + 1);
    
    if(!buffer){
        printf("couldn't allocate memory for file");
        exit(1);
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    return buffer;
}

char help[] = 
"usage: %s [options] [file]\n"
"\n"
"options:\n"
"  -h, --help  print this screen\n";


int main(int argc, char* argv[]){
    if(argc == 1){
        printf("repl");
    } else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
        printf(help, argv[0]);
    } else {
        char* data = readfile(argv[1]);
        parse(data);
    }
}
