all: hw8 shell

hw8: main.o

ifeq (${OS}, Windows_NT)
	g++ -o hw8 main.o atom.o number.o variable.o struct.o proxy.o list.o node.o term.o -lgtest
else
	g++ -o hw8 main.o atom.o number.o variable.o struct.o proxy.o list.o node.o term.o -lgtest -lpthread
endif

shell: shell.o
ifeq (${OS}, Windows_NT)
	g++ -o shell shell.o atom.o number.o variable.o struct.o proxy.o list.o node.o term.o -lgtest
else
	g++ -o shell shell.o atom.o number.o variable.o struct.o proxy.o list.o node.o term.o -lgtest -lpthread
endif

main.o: main.cpp utList.h atom.h atom.cpp number.h number.cpp variable.h variable.cpp struct.h struct.cpp list.h list.cpp term.h term.cpp proxy.h proxy.cpp utProxy.h scanner.h utScanner.h parser.h utParser.h global.h node.h node.cpp iterator.h utIterator.h
	g++ -std=gnu++0x -c main.cpp term.cpp atom.cpp number.cpp variable.cpp struct.cpp proxy.cpp list.cpp node.cpp

shell.o: shell.cpp
	g++ -std=gnu++0x -c shell.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw8 shell
endif

