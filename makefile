# compiler
CC = g++

# compiler options
CFLAGS = -c -Wall

all: ProgramTester

ProgramTester: ProgramTester.o
	$(CC) -lm ProgramTester.o -o ProgramTester

ProgramTester.o: ProgramTester.cpp
	$(CC) $(CFLAGS) ProgramTester.cpp

clean:
	rm -rf *o ProgramTester
