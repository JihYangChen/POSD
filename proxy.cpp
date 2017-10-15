#include "proxy.h"

Proxy::Proxy(string proxyValue) : _nextProxy(NULL), _proxyValue(proxyValue), _proxyTerm(NULL) {}

string Proxy::getProxyValue() const {
    return _proxyValue;
}

void Proxy::setProxyValue(string s) {
    _proxyValue = s;
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
