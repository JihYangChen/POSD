#include "atom.h"

string Atom::symbol() const {
    return _symbol;
}

string Atom::value() const {
    return _symbol;
}

bool Atom::match(Term &term) {
    return symbol() == term.symbol();
}
