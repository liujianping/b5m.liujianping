#Makefile for Problem B

INSTALL_DIR=
CC=g++
HEADER=*.h
SROUCE=GramHash.cpp GramHeap.cpp GramLanguager.cpp GramClassifier.cpp
OBJECT=DocSet.o DocVector.o NBClassifier.o DAGNBClassifier.o
FLAGS=-O -g 
#FLAGS=-O -g -D_DEBUG

.cpp.o:
	$(CC) $(FLAGS) -c $*.cpp
	
all: Problem_NB Problem_DAGNB
	    
Problem_NB: Problem_NB.o $(OBJECT)
	$(CC) $(FLAGS) -o Problem_NB $(OBJECT) Problem_NB.o $(HEADER)


Problem_DAGNB: Problem_DAGNB.o $(OBJECT)
	$(CC) $(FLAGS) -o Problem_DAGNB $(OBJECT) Problem_DAGNB.o $(HEADER)

clean:
	rm -f *.o Problem_NB Problem_DAGNB

