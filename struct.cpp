#include "struct.h"

Struct::Struct(Atom const &name, std::vector<Term *> args) : _name(name), _args(args) {}

Term * Struct::args(int index) {
    return _args[index];
}

Atom Struct::name() {
    return _name;
}

string Struct::symbol() const {
    string returnStr = _name.symbol() + "(";
    
    for (int i=0; i<_args.size()-1; i++) {
        returnStr += _args[i] -> symbol() + ", ";
    }
    
    returnStr += _args[_args.size()-1]->symbol() + ")";
        
    return returnStr;
}

string Struct::value() const {
    return symbol();
}

bool Struct::match(Term &term) {
    Struct *ps = dynamic_cast<Struct *>(&term);
    if (ps) {
        if (!_name.match(ps->_name))
            return false;
        if (_args.size() != ps->_args.size())
            return false;
        for (int i=0; i<_args.size(); i++) {
            if(!args(i)->match(*(ps->args(i))))
                return false;
        }
        return true;
    }
    
    return false;
}
