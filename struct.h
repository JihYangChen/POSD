#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>

class Struct : public Term
{
public:
    Struct(Atom const &name, std::vector<Term *> args);
    Term * args(int index);
    Atom name();
    string symbol() const;
    string value() const;
    bool match(Term &term);
    
private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif