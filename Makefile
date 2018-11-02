
OBJS=scanner.o parser.o ast.o interpreter.o
INTERM=scanner.c parser.c parser.h
PROGRAM=./interpreter
CFLAGS=-g 

all: $(PROGRAM)

scanner.c: scanner.flex parser.h
	flex -o scanner.c scanner.flex

parser.c parser.h: parser.bison
	bison --defines=parser.h -o parser.c parser.bison

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS)
clean:
	rm -f $(PROGRAM) $(OBJS) $(INTERM)

test: $(PROGRAM)
	$(PROGRAM) inputExample.m
	$(PROGRAM) ifExample4.m
	$(PROGRAM) ifExample3.m
	$(PROGRAM) ifExample2.m
	$(PROGRAM) ifExample.m
	$(PROGRAM) fibonacci.m
	$(PROGRAM) forExample.m
	$(PROGRAM) forExample2.m
	$(PROGRAM) whileExample2.m
	$(PROGRAM) whileExample.m
	$(PROGRAM) arithmeticOperators.m
	$(PROGRAM) arithmeticOperators2.m