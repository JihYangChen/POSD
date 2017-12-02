#include "term.h"
#include "iterator.h"

Iterator<Term *> * Term::createIterator(){
    return new NullIterator<Term *>(this);
}
