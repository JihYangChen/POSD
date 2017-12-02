#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>

template <class T>
class Iterator;

class Struct : public Term
{
public:
    Struct(Atom const &name, std::vector<Term *> args);
    Term * args(int index);
    Atom name();
    string symbol() const;
    string value() const;
    int arity();
    bool match(Term &term);
    Iterator<Term *> * createIterator();
    Iterator<Term *> * createDFSIterator();
    Iterator<Term *> * createBFSIterator();
    
private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif
