#ifndef NODE_H
#define NODE_H

#include "term.h"

enum Operators {TERM, SEMICOLON, COMMA, EQUALITY};

class Node {
public:
    
    Operators payload;
    Term *term;
    Node *left, *right;
    
    Node(Operators op):payload(op), term(0), left(0), right(0) {}
    Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}
    
    bool evaluate();
};

#endif
