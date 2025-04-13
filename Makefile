CC = cc
FLAGS = -Wall

liv: main.o
	$(CC) $(FLAGS) -o liv main.o lexer.o parser.o
	rm -f *.o

main.o: parser.o
	$(CC) $(FLAGS) -c main.c

parser.o: lexer.o nodes.o
	$(CC) $(FLAGS) -c lib/parser.c lib/parser.h

lexer.o: token.o
	$(CC) $(FLAGS) -c lib/lexer.c lib/lexer.h
	
token.o:
	$(CC) $(FLAGS) -c lib/token.h

nodes.o:
	$(CC) $(FLAGS) -c lib/nodes.h

clean:
	rm -f *.o liv */*.gch

run: clean liv
	./liv $(path)
