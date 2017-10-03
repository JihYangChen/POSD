#ifndef ATOM_H
#define ATOM_H

#include "term.h"

class Atom : public Term {
public:
    Atom (string s) : Term(s) { }
    bool match(Term &term) { return this->symbol() == term.symbol(); }
    bool match(Variable &variable) { return variable.match(*this); }
};

#endif
