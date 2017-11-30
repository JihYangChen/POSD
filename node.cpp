#include "node.h"
#include "iterator.h"

bool Node::evaluate() {
    
    switch (payload) {
        case EQUALITY:
            return (left->term) -> match(*(right->term));
            break;
            
        case COMMA:
            return (left->evaluate()) && (right->evaluate());
            break;
            
        case SEMICOLON:
        {
            bool leftMatchingResult = left->evaluate();
            bool rightMatchingResult = right->evaluate();
            return leftMatchingResult || rightMatchingResult;
            
        }
            break;
            
        default:
            return false;
    }
}

Iterator * Node::createDFSIterator() {
    return new DFSIterator(this);
}

Iterator * Node::createBFSIterator() {
    return new BFSIterator(this);
}
