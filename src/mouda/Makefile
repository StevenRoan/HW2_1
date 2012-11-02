CC=g++
CPPFLAGS=-g -D_DEBUG_=5
#CPPFLAGS=

all: readData.o inference.o writeData.o hw2_1

hw2_1: readData.o inference.o writeData.o
	$(CC) readData.o inference.o writeData.o -o hw2_1 

readData.o: readData.cpp
	$(CC) $(CPPFLAGS) -o readData.o -c readData.cpp

inference.o: inference.h inference.cpp
	$(CC) $(CPPFLAGS) -o inference.o -c inference.cpp 

writeData.o: writeData.cpp
	$(CC) $(CPPFLAGS) -o writeData.o -c writeData.cpp

clean:
	rm -f hw2_1 *.o
