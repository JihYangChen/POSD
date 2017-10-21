#include "list.h"
#include <iostream>

List::List() { }

List::List(vector<Term *> const & elements) : _elements(elements) { }

Term * List::getElement(int index) const {
    return _elements[index];
}

string List::symbol() const {
    string returnString = "[";
    for (int i=0; i<((int)_elements.size()-1); i++) {
        returnString += getElement(i)->symbol() + ", ";
    }
    if (_elements.size())
        returnString += getElement((int)_elements.size()-1) -> symbol();
    returnString += "]";
    
    return returnString;
}

string List::value() const {
    string returnString = "[";
    for (int i=0; i<((int)_elements.size()-1); i++) {
        returnString += getElement(i)->value() + ", ";
    }
    if (_elements.size())
        returnString += getElement((int)_elements.size()-1) -> value();
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
            if(!getElement(i)->match(*(listPtr->getElement(i))))
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
        throw "Accessing head in an empty list";
    else
        return getElement(0);
}

List * List::tail() const {
    if (_elements.empty())
        throw "Accessing tail in an empty list";
    else {
        vector<Term *> tailListElements(++(_elements.begin()), _elements.end());
        List * tailListPtr = new List(tailListElements);
        
        return tailListPtr;
    }
}
