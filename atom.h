#ifndef ATOM_H
#define ATOM_H

#include "term.h"
#include "variable.h"

class Atom : public Term {
private:
	string _symbol;

public:
    Atom (string s);
    string symbol() const;
    string value() const;
    bool match(Term &term);
};


#endif
