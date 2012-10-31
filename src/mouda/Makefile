CC=g++
CPPFLAGS=-g -D_DEBUG_=2
#CPPFLAGS=

all: readData.o inference.o hw2_1

hw2_1: readData.o inference.o
	$(CC) readData.o inference.o -o hw2_1 

readData.o: readData.cpp
	$(CC) $(CPPFLAGS) -o readData.o -c readData.cpp

inference.o: inference.h inference.cpp
	$(CC) $(CPPFLAGS) -o inference.o -c inference.cpp 
clean:
	rm -f hw2_1 *.o
