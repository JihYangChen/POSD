#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "atom.h"

class Expression {
public:
    virtual bool evaluate() = 0;
    virtual string getExpressionString() = 0;
};


class MatchExp : public Expression {
public:
    MatchExp(Term* left, Term* right): _left(left), _right(right){
        
    }
    
    bool evaluate(){
        return _left->match(*_right);
    }
    
    string getExpressionString() {
        
        if (findMatchingExpression(_left->symbol() + " = " + _right->value()))
            return "";
        else {
            _matchingExpressions.push_back(_left->symbol() + " = " + _right->value());
            if (_left->symbol() == _right->symbol())
                return "true";
            else if (this->evaluate())
                return _left->symbol() + " = " + _right->value();
            else
                return "false";
        }
    }
    
    bool findMatchingExpression(string exp) {
        for (vector<string>::iterator it = _matchingExpressions.begin(); it < _matchingExpressions.end(); ++it) {
            if ((*it) == exp)
                return true;
        }
        return false;
    }
    
    static void clearMathcingExpressions() {
        _matchingExpressions.clear();
    }
    
private:
    Term* _left;
    Term* _right;
    static vector<string> _matchingExpressions;
};
vector<string> MatchExp::_matchingExpressions = {};

class ConjExp : public Expression {
public:
    ConjExp(Expression *left, Expression *right) : _left(left), _right(right) {
        
    }
    
    bool evaluate() {
        return (_left->evaluate() && _right->evaluate());
    }
    
    string getExpressionString() {
        if (!evaluate())
            return "false";
        string leftStr = _left->getExpressionString();
        string rightStr = _right->getExpressionString();

        if (leftStr=="" || rightStr=="")
            return leftStr + rightStr;
        else if (leftStr == "true")
            return rightStr;
        else if (rightStr == "true")
            return leftStr;
        else
            return leftStr + ", " + rightStr;
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
    
    string getExpressionString() {
        string leftStr = _left->getExpressionString();
        MatchExp::clearMathcingExpressions();
        string rightStr = _right->getExpressionString();
        
        if (leftStr=="false")
            return rightStr;
        else if (rightStr=="false")
            return leftStr;
        else
            return leftStr + "; " + rightStr;
    }
    
private:
    Expression * _left;
    Expression * _right;
};

#endif
