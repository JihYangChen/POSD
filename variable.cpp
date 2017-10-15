#include "variable.h"

Variable::Variable(string s) : _symbol(s), _proxyList(NULL) {}

string Variable::symbol() const {
    return _symbol;
}

string Variable::value() const {
    if(!_proxyList)
        return symbol();
    
    if(!isAssignable())
        return getProxyRoot()->getProxyTerm()->value();
    else
        return getProxyRoot()->getProxyString();
}

Proxy * Variable::getProxyRoot() const {
    return _proxyList -> getProxyRoot();
}

bool Variable::isAssignable() const {
    if (!_proxyList)
        return true;
    else
        return !getProxyRoot()->getProxyTerm();
}

bool Variable::match(Term &term) {
    Variable *variable = dynamic_cast<Variable * >(&term);
    // Variable.match(Variable)
    if (variable) {
        if (!_proxyList && !variable->_proxyList) {
            // match itself
            if(variable == this)
                return true;
            _proxyList = new Proxy(variable->symbol());
            variable->_proxyList = _proxyList;
        }
        else if (_proxyList && !variable->_proxyList) {
            variable->_proxyList = getProxyRoot();
            getProxyRoot()->setProxyString(variable -> symbol());
        }
        else if (!_proxyList && variable->_proxyList) {
            _proxyList = variable->getProxyRoot();
            getProxyRoot()->setProxyString(symbol());
        }
        else if (_proxyList && _proxyList) {
            // Both root's proxyTerm is empty.
            if (!(getProxyRoot()->getProxyTerm()) && !(variable->getProxyRoot()->getProxyTerm())) {
                Proxy *newProxy = new Proxy(variable->getProxyRoot()->getProxyString());
                getProxyRoot() -> setNextProxy(newProxy);
                variable -> getProxyRoot() -> setNextProxy(newProxy);
            }
            // Either root's proxyTerm is empty.
            else if ((getProxyRoot()->getProxyTerm()) && !(variable->getProxyRoot()->getProxyTerm())) {
                variable->getProxyRoot()->setNextProxy(getProxyRoot());
            }
            else if (!(getProxyRoot()->getProxyTerm()) && (variable->getProxyRoot()->getProxyTerm())) {
                getProxyRoot()->setNextProxy(variable->getProxyRoot());
            }
            // Neither root's proxyTerm is empty.
            else if ((getProxyRoot()->getProxyTerm()) && (variable->getProxyRoot()->getProxyTerm())) {
                Term *leftProxyTerm = getProxyRoot()->getProxyTerm();
                Term *rightProxyTerm = variable->getProxyRoot()->getProxyTerm();
                return leftProxyTerm->match(*rightProxyTerm);
            }
        }
        return true;
    }
    
    // Variable.match(Term)
    if (isAssignable()){
        if (!_proxyList)
            _proxyList = new Proxy(symbol());
        getProxyRoot() -> setProxyTerm(&term);
        return true;
    }
    else {
        Term *proxyTerm = getProxyRoot()->getProxyTerm();
        return proxyTerm->match(term);
    }

    
}
