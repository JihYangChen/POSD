#ifndef TERM_H
#define TERM_H

#include <string>

using std::string;

class Term{

private:
    
public:
	virtual string symbol() const = 0;
    virtual string value() const = 0;
	virtual bool match(Term &term) = 0;
};

#endif
