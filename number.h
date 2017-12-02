#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include "variable.h"
#include "iterator.h"
#include <sstream>

class Number : public Term {
private:
    string _symbol;
    
public:
    Number (double);
    string symbol() const;
    string value() const;
    bool match(Term &);
};


#endif /* number_h */
