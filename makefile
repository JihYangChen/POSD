INC_DIR = include

all: hw1

hw1: main.o Shapes.o Media.o Sort.o
ifeq (${OS}, Windows_NT)
	g++ -o hw1 main.o Shapes.o Media.o Sort.o -lgtest
else
	g++ -o hw1 main.o Shapes.o Media.o Sort.o -lgtest -lpthread
endif
	
main.o: main.cpp utsort.h
	g++ -std=gnu++0x -c main.cpp
Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
	g++ -std=gnu++0x -c Shapes.cpp
Media.o: $(INC_DIR)/Media.h Media.cpp
	g++ -std=gnu++0x -c Media.cpp
Sort.o: $(INC_DIR)/Sort.h Sort.cpp
	g++ -std=gnu++0x -c Sort.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw1
endif
