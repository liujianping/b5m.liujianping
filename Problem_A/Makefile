#Makefile for Problem A

INSTALL_DIR=
CC=g++
HEADER=*.h
SROUCE=GramHash.cpp GramHeap.cpp GramLanguager.cpp GramClassifier.cpp
OBJECT=GramHash.o GramHeap.o GramLanguager.o GramClassifier.o
FLAGS=-O -g 
#FLAGS=-O -g -D_DEBUG

.cpp.o:
	$(CC) $(FLAGS) -c $*.cpp
 
all: Problem_A_1 Problem_A_2
	
Problem_A_1: Problem_A_1.o $(OBJECT)
	$(CC) $(FLAGS) -o Problem_A_1 $(OBJECT) Problem_A_1.o $(HEADER)


Problem_A_2: Problem_A_2.o $(OBJECT)
	$(CC) $(FLAGS) -o Problem_A_2 $(OBJECT) Problem_A_2.o $(HEADER)

clean:
	rm -f *.o Problem_A_1 Problem_A_2

