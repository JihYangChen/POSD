#ifndef VARIABLE_H
#define VARIABLE_H

#include "term.h"

class Variable : public Term {
public:
    Variable(string s) : Term(s){}
    string value(){ return _value; }
    
    bool match(Term *term) {
        bool ret = _assignable;
        if(_assignable){
          _value = (term -> symbol()) ;
          _assignable = false;
        }
        else if(_value == term -> symbol())
            ret = true;
        return ret;
    }

private:
  string _value;
  bool _assignable = true;
};

#endif
