all: hw5

hw5: main.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 main.o atom.o number.o variable.o struct.o proxy.o list.o scanner.o -lgtest
else
	g++ -o hw5 main.o atom.o number.o variable.o struct.o proxy.o list.o scanner.o -lgtest -lpthread
endif

main.o: main.cpp utList.h atom.h atom.cpp number.h number.cpp variable.h variable.cpp struct.h struct.cpp list.h list.cpp term.h proxy.h proxy.cpp scanner.h scanner.cpp utScanner.h global.h
	g++ -std=gnu++0x -c main.cpp atom.cpp number.cpp variable.cpp struct.cpp proxy.cpp list.cpp scanner.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw5
endif
