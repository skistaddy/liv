CC = cc
FLAGS = -Wall

liv: main.o parser.o lexer.o
	$(CC) $(FLAGS) -o $@ $^
	rm -f *.o

main.o: main.c lib/parser.h
	$(CC) $(FLAGS) -c main.c

parser.o: lib/parser.c lib/parser.h lib/nodes.h lib/lexer.h
	$(CC) $(FLAGS) -c lib/parser.c

lexer.o: lib/lexer.c lib/lexer.h lib/token.h
	$(CC) $(FLAGS) -c lib/lexer.c
	
.PHONY: clean rebuild run

clean:
	rm -f *.o liv */*.gch

rebuild: clean liv

run: liv
	./liv $(path)
