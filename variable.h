#ifndef VARIABLE_H
#define VARIABLE_H

#include "term.h"
#include "proxy.h"

class Variable : public Term {
public:
    Variable(string s);
    string symbol() const;
    string value() const;
    bool match(Term &term);
    Proxy * getProxyRoot() const;
    bool isAssignable() const;
    
private:
    string _symbol;
    Proxy *_proxyList;
};

#endif
