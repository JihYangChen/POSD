#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include <sstream>

std::string intConvertToString(int num);

class Number : public Term {
private:
    const std::string _value;
    
public:
    Number(int num) : _value(intConvertToString(num)), Term(intConvertToString(num)) { }
    string value(void) const { return _value; }
    bool match(Term *term) { return this->symbol() == term -> symbol(); }
    bool match(Variable *variable) { return variable -> match(this); }
};

std::string intConvertToString(int num) {
    std::string convertStr;
    std::stringstream ss;
    ss << num;
    ss >> convertStr;
    return convertStr;
}

#endif /* number_h */
