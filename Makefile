all: lr_parser

CC = gcc 
FLAGS = -Wall -Wextra
OBJ = stack.o parser.o string.o graph.o main.o

lr_parser: $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

%.o:%.c
	$(CC) $(FLAGS) -c $<

parser.o: parser.h
string.o: string.h
stack.o: stack.h
graph.o: string.h string.o parser.h parser.o graph.h
main.o: parser.h parser.o stack.h stack.o string.h string.o graph.h graph.o
