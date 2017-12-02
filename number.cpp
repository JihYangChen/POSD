#include "number.h"

Number::Number (double value) {
    std::stringstream ss;
    ss << value;
    ss >> _symbol;
}

string Number::symbol() const {
    return _symbol;
}

string Number::value() const {
    return _symbol;
}

bool Number::match(Term &term) {
    Variable *variable = dynamic_cast<Variable *> (&term);
    // term's type is Variable
    if(variable)
        return variable->match(*this);
    
    // term's type isn't Variable
    else
        return symbol() == term.symbol();
}
