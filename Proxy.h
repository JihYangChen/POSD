#ifndef Proxy_h
#define Proxy_h

#include "term.h"
#include <string>
using std::string;

class Proxy {
private:
    Proxy *_nextProxy;
    Term *_proxyTerm;
    string _proxyValue;
    
public:
    Proxy(string proxyValue);
    string getProxyValue() const;
    void setProxyValue(string s);
    Proxy * getProxyRoot();
    void setNextProxy(Proxy *nextProxy);
    Term * getProxyTerm() const;
    void setProxyTerm(Term *term);
};

#endif /* Proxy_h */
