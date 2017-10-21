all: utTerm

utTerm: main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o atom.o number.o variable.o struct.o proxy.o list.o -lgtest
else
	g++ -o hw4 main.o atom.o number.o variable.o struct.o proxy.o list.o -lgtest -lpthread
endif

main.o: main.cpp utList.h atom.h atom.cpp number.h number.cpp variable.h variable.cpp struct.h struct.cpp list.h list.cpp term.h proxy.h proxy.cpp
	g++ -std=gnu++0x -c main.cpp atom.cpp number.cpp variable.cpp struct.cpp proxy.cpp list.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif
