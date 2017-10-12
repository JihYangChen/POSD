#ifndef Term_h
#define Term_h

#include <string>
using std::string;

class Term {
private:
    const std::string _symbol;
    
public:
    Term(string s) : _symbol(s){}
    virtual bool match(Term &term) = 0;
    string symbol(void) const { return _symbol; }
};

#endif /* Term_h */
