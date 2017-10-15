#include "atom.h"

Atom::Atom (string s) : _symbol(s) {}

string Atom::symbol() const {
    return _symbol;
}

string Atom::value() const {
    return _symbol;
}

bool Atom::match(Term &term) {
    Variable *variable = dynamic_cast<Variable *> (&term);
    // term's type is Variable
    if(variable)
        return variable->match(*this);
    
    // term's type isn't Variable
    else
        return symbol() == term.symbol();
}
