#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include "variable.h"
#include <sstream>

class Number : public Term {
private:
    string _symbol;
    
public:
    Number (double value);
    string symbol() const;
    string value() const;
    bool match(Term &term);
};


#endif /* number_h */
