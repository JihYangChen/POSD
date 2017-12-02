#include <iostream>
#include "list.h"
#include "iterator.h"

List::List() { }

List::List(vector<Term *> const & elements) : _elements(elements) { }

Term * List::args(int index) const {
    return _elements[index];
}

string List::symbol() const {
    string returnString = "[";
    for (int i=0; i<((int)_elements.size()-1); i++) {
        returnString += args(i)->symbol() + ", ";
    }
    if (_elements.size())
        returnString += args((int)_elements.size()-1) -> symbol();
    returnString += "]";
    
    return returnString;
}

string List::value() const {
    string returnString = "[";
    for (int i=0; i<((int)_elements.size()-1); i++) {
        returnString += args(i)->value() + ", ";
    }
    if (_elements.size())
        returnString += args((int)_elements.size()-1) -> value();
    returnString += "]";
    
    return returnString;
}

bool List::match(Term &term) {
    List *listPtr = dynamic_cast<List *>(&term);
    // term's type is List
    if (listPtr) {
        if (_elements.size() != listPtr->_elements.size())
            return false;
        for (int i=0; i<_elements.size(); i++) {
            if(!args(i)->match(*(listPtr->args(i))))
                return false;
        }
        return true;
    }
    
    Variable *variable = dynamic_cast<Variable *> (&term);
    // term's type is Variable
    if(variable)
        return variable->match(term);
    
    // term's type isn't Variable or List
    return false;
}

Term * List::head() const {
    if (_elements.empty())
        throw string("Accessing head in an empty list");
    else
        return args(0);
}

List * List::tail() const {
    if (_elements.empty())
        throw string("Accessing tail in an empty list");
    else {
        vector<Term *> tailListElements(++(_elements.begin()), _elements.end());
        List * tailListPtr = new List(tailListElements);
        
        return tailListPtr;
    }
}

int List::arity() {
    return static_cast<int>(_elements.size());
}

Iterator<Term *> * List::createIterator()
{
    return new ListIterator<Term *>(this);
}

Iterator<Term *> * List::createDFSIterator()
{
    return new DFSIterator<Term *>(this);
}

Iterator<Term *> * List::createBFSIterator()
{
    return new BFSIterator<Term *>(this);
}
