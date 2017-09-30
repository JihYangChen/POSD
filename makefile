all: utTerm

utTerm: mainTerm.o
ifeq (${OS}, Windows_NT)
    g++ -o hw2 mainTerm.o -lgtest
else
	g++ -o hw2 mainTerm.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h atom.h variable.h Number.h term.h
	g++ -std=gnu++0x -c mainTerm.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o madRace utAtom hw2 utVariable utTerm
endif
