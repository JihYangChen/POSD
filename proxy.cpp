#include "proxy.h"

Proxy::Proxy(string ProxyString) : _nextProxy(NULL), _proxyString(ProxyString), _proxyTerm(NULL) {}

string Proxy::getProxyString() const {
    return _proxyString;
}

void Proxy::setProxyString(string s) {
    _proxyString = s;
}

Proxy * Proxy::getProxyRoot() {
    if (this->_nextProxy == NULL)
        return this;
    else
        return this->_nextProxy->getProxyRoot();
}

void Proxy::setNextProxy(Proxy *nextProxy) {
    _nextProxy = nextProxy;
}

Term * Proxy::getProxyTerm() const {
    return _proxyTerm;
}

void Proxy::setProxyTerm(Term *term) {
    _proxyTerm = term;
}
