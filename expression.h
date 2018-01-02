#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "atom.h"

class Expression {
public:
    virtual bool evaluate() = 0;
};


class MatchExp : public Expression {
public:
    MatchExp(Term* left, Term* right): _left(left), _right(right){
        
    }
    
    bool evaluate(){
        return _left->match(*_right);
    }
    
private:
    Term* _left;
    Term* _right;
};

class ConjExp : public Expression {
public:
    ConjExp(Expression *left, Expression *right) : _left(left), _right(right) {
        
    }
    
    bool evaluate() {
        return (_left->evaluate() && _right->evaluate());
    }
    
private:
    Expression * _left;
    Expression * _right;
};

class DisjExp : public Expression {
public:
    DisjExp(Expression *left, Expression *right) : _left(left), _right(right) {
        
    }
    
    bool evaluate() {
        return (_left->evaluate() || _right->evaluate());
    }
    
private:
    Expression * _left;
    Expression * _right;
};

#endif
