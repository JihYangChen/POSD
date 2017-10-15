all: utTerm

utTerm: main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 main.o -lgtest
else
	g++ -o hw3 main.o atom.o number.o variable.o struct.o proxy.o -lgtest -lpthread
endif

main.o: main.cpp utVariable.h utStruct.h atom.h atom.cpp number.h number.cpp variable.h variable.cpp struct.h struct.cpp term.h proxy.h proxy.cpp
	g++ -std=gnu++0x -c main.cpp atom.cpp number.cpp variable.cpp struct.cpp proxy.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
