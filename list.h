#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "variable.h"

#include <vector>
using std::vector;

template <class T>
class Iterator ;

class List : public Term {
public:
    List ();
    List (vector<Term *> const & elements);
    Term * args(int index) const;
    string symbol() const;
    string value() const;
    bool match(Term & term);
    Term * head() const;
    List * tail() const;
    int arity();
    Iterator<Term *>* createIterator();
    Iterator<Term *>* createDFSIterator();
    Iterator<Term *>* createBFSIterator();
    
private:
    vector<Term *> _elements;
    
};

#endif
