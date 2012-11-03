CC=g++
CPPFLAGS=-g -D_DEBUG_=11
#CPPFLAGS=

all: main.o inference.o writeData.o hw2_1

hw2_1: main.o inference.o writeData.o
	$(CC) main.o inference.o writeData.o -o hw2_1 

main.o: inference.h writeData.h main.cpp
	$(CC) $(CPPFLAGS) -o main.o -c main.cpp

inference.o:  inference.cpp
	$(CC) $(CPPFLAGS) -o inference.o -c inference.cpp 

writeData.o: writeData.cpp
	$(CC) $(CPPFLAGS) -o writeData.o -c writeData.cpp

clean:
	rm -f hw2_1 *.o
