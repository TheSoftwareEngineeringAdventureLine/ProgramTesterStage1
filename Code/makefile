# compiler
CC = g++

# compiler options
CFLAGS = -c -Wall

all: mytest

mytest: testmain.o prog1.o
	$(CC) -lm testmain.o prog1.o -o mytest

testmain.o: testmain.cpp mytest.h
	$(CC) $(CFLAGS) testmain.cpp 

prog1.o: prog1.cpp mytest.h
	$(CC) $(CFLAGS) prog1.cpp

clean:
	rm -rf *o mytest
