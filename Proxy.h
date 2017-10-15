#ifndef PROXY_H
#define PROXY_H

#include "term.h"
#include <string>
using std::string;

class Proxy {
private:
    Proxy *_nextProxy;
    Term *_proxyTerm;
    string _proxyString;
    
public:
    Proxy(string proxyString);
    string getProxyString() const;
    void setProxyString(string s);
    Proxy * getProxyRoot();
    void setNextProxy(Proxy *nextProxy);
    Term * getProxyTerm() const;
    void setProxyTerm(Term *term);
};

#endif /* Proxy_h */
