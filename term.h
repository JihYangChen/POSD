#ifndef TERM_H
#define TERM_H

#include <string>
using std::string;

template <class T>
class Iterator;

class Term{
private:
    
public:
	virtual string symbol() const = 0;
    virtual string value() const = 0;
	virtual bool match(Term &term) = 0;
    virtual Iterator<Term *> * createIterator();
    virtual ~Term() {}
};

#endif
