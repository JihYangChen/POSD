all: hw7

hw7: main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 main.o atom.o number.o variable.o struct.o proxy.o list.o node.o -lgtest
else
	g++ -o hw7 main.o atom.o number.o variable.o struct.o proxy.o list.o node.o -lgtest -lpthread
endif

main.o: main.cpp utList.h atom.h atom.cpp number.h number.cpp variable.h variable.cpp struct.h struct.cpp list.h list.cpp term.h proxy.h proxy.cpp utProxy.h scanner.h utScanner.h parser.h utParser.h global.h node.h node.cpp iterator.h utIterator.h
	g++ -std=gnu++0x -c main.cpp atom.cpp number.cpp variable.cpp struct.cpp proxy.cpp list.cpp node.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7
endif
