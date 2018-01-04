#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <stack>
using std::stack;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"
#include "expression.h"

class Parser {
public:
    Parser(Scanner scanner) : _scanner(scanner){}
    Term* createTerm() {
        int token = _scanner.nextToken();
        _currentToken = token;
        Term *newTerm = nullptr;
        
        // Create Variable
        if(token == VAR){
            newTerm = new Variable(symtable[_scanner.tokenValue()].first);
        }
        
        // Create Number
        else if (token == NUMBER){
            newTerm = new Number(_scanner.tokenValue());
        }
        
        // Create Atom or Struct
        else if (token == ATOM || token == ATOMSC){
            Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
            
            // Create Struct
            if(_scanner.nextToken() == '(') {
                newTerm = createStructure(*atom);
            }
            // Create Atom
            else {
                _scanner.positionBackward();
                newTerm =  atom;
            }
        }
        
        // Create List
        else if (token == '[') {
            newTerm =  createList();
        }
        
        else {
            return nullptr;
        }
        
        Term *existTerm = findTermExistInTerms(*newTerm);
        if(existTerm) {
            delete newTerm;
            return existTerm;
        }
        else
            return newTerm;
        
    }
    
    vector<Term*> getTerms() {
        return _terms;
    }
    
    void matchings() {
        vector<Node *> nodes;
        
        readSentenceAndCreateNodes(nodes);
        reverse(nodes.begin(), nodes.end());
        inorderToPreorder(nodes);
        reverse(nodes.begin(), nodes.end());
        _expressionTree = buildExpressionTree(nodes);
    }
    
    Node * expressionTree() {
        return _expressionTree;
    }
    
    /* Build interpreter's expression */
    
    void buildExpression(){
        disjunctionMatch();
        restDisjunctionMatch();
        if (createTerm() == nullptr)
            throw string("Missing token '.'");
    }
    
    Expression* getExpressionTree(){
        return _expStack.top();
    }
    
    void disjunctionMatch() {
        conjunctionMatch();
        restConjunctionMatch();
    }
    
    void restDisjunctionMatch() {
        if (_scanner.currentChar() == ';') {
            createTerm();
            _termsContexStartPosition = static_cast<int>(_terms.size());
            disjunctionMatch();
            Expression *right = _expStack.top();
            _expStack.pop();
            Expression *left = _expStack.top();
            _expStack.pop();
            _expStack.push(new DisjExp(left, right));
            restDisjunctionMatch();
        }
    }
    
    void conjunctionMatch() {
        Term * left = createTerm();
        if (left->symbol() == ".")
            throw string("Unexpected ',' before '.'");
        _terms.push_back(left);
        if (createTerm() == nullptr && _currentToken == '=') {
            Term * right = createTerm();
            _terms.push_back(right);
            _expStack.push(new MatchExp(left, right));
        } else {
            if (_currentToken == ';')
                throw string("Unexpected ';' before '.'");
            else if (_currentToken == ',')
                throw string("Unexpected ',' before '.'");
            else
                throw string(left->symbol() + " does never get assignment");
        }
    }
    
    void restConjunctionMatch() {
        if (_scanner.currentChar() == ',') {
            createTerm();
            conjunctionMatch();
            Expression *right = _expStack.top();
            _expStack.pop();
            Expression *left = _expStack.top();
            _expStack.pop();
            _expStack.push(new ConjExp(left, right));
            restConjunctionMatch();
        }
    }
    
    string getResult() {
        Expression *expressionTree = getExpressionTree();
//        if (expressionTree -> evaluate()) {
        string returnStr = expressionTree -> getExpressionString() + ".";
        MatchExp::clearMathcingExpressions();
        return returnStr;
//        }
//        else
//            return "false.";
    }
    
    

private:
    FRIEND_TEST(ParserTest, createArgs);
    FRIEND_TEST(ParserTest,ListOfTermsEmpty);
    FRIEND_TEST(ParserTest,listofTermsTwoNumber);
    FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
    
    FRIEND_TEST(ParserTest, ReadSentenceAndCreateNodes);
    FRIEND_TEST(ParserTest, InorderToPreorder);
    
    Term * createStructure(Atom & structName) {
        int startIndexOfStructArgs = (int)_terms.size();
        createTerms();
        
        if(_scanner.nextToken() != ')')
            throw string("Unbalanced operator");
        
        vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
        _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
        
        return new Struct(structName, args);
    }
    
    Term * createList() {
        int startIndexOfListArgs = (int)_terms.size();
        createTerms();
        
        if(_scanner.nextToken() != ']')
            throw string("Unbalanced operator");
        
        vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
        _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
        
        return new List(args);
    }
    
    // Create a vector of arguments in _terms, the right parentheses and square brackets will NOT be discarded(nextToken will be ')' or ']') after calling.
    void createTerms()
    {
        Term* term = createTerm();
        if (term) {
            _terms.push_back(term);
            while (_scanner.nextToken() == ',') {
                _terms.push_back(createTerm());
            }
            
            // Right parentheses
            _scanner.positionBackward();
        }
        // Empty Struct or List
        else {
            _scanner.positionBackward();
        }
    }
    
    Term* findTermExistInTerms(Term &term) {
        vector<Term *>::iterator it = _terms.begin() + _termsContexStartPosition;
        
        for ( ; it<_terms.end(); it++) {
            if ((*it) -> symbol() == term.symbol())
                return *it;
            
            Struct *ps = dynamic_cast<Struct *>(*it);
            if(ps)
                return findTermExistInArgs(*ps, term);
            
            List *pl = dynamic_cast<List *>(*it);
            if(pl)
                return findTermExistInArgs(*pl, term);
        }
        return nullptr;
    }
    
    template <class TermType>
    Term* findTermExistInArgs(TermType &argsObject, Term &term) {
        for (int i=0; i<argsObject.arity(); i++) {
            if (argsObject.args(i)->symbol() == term.symbol())
                return argsObject.args(i);
            
            Struct *ps = dynamic_cast<Struct *>(argsObject.args(i));
            if(ps)
                return findTermExistInArgs(*ps, term);
            
            List *pl = dynamic_cast<List *>(argsObject.args(i));
            if(pl)
                return findTermExistInArgs(*pl, term);
        }
        return nullptr;
    }
    
    void readSentenceAndCreateNodes(vector<Node *> &nodes) {
        Term *term;
        if ((term = createTerm())) {
            _terms.push_back(term);
            nodes.push_back(new Node(TERM, term, nullptr, nullptr));
            
            int token;
            while ((token = _scanner.nextToken()) != ATOMSC) {
                if (token == '=')
                    nodes.push_back(new Node(EQUALITY));
                else if (token == ',')
                    nodes.push_back(new Node(COMMA));
                else if (token == ';'){
                    nodes.push_back(new Node(SEMICOLON));
                    _termsContexStartPosition = static_cast<int>(_terms.size());
                }
                
                term = createTerm();
                _terms.push_back(term);
                nodes.push_back(new Node(TERM, term, nullptr, nullptr));
            }
        }
    }
    
    void inorderToPreorder(vector<Node *> &inputNodes) {
        stack<Node *> stack;
        vector<Node *>  outputNodes;
        
        reverse(inputNodes.begin(), inputNodes.end());
        
        for (vector<Node *>::iterator it = inputNodes.begin(); it<inputNodes.end(); it++) {
            Node* node = *it;
            if (node->payload == TERM)
                outputNodes.push_back(node);
            else if ((stack.empty()) || (node->payload >= stack.top()->payload))
                stack.push(node);
            else {
                while (node -> payload < stack.top()->payload){
                    outputNodes.push_back(stack.top());
                    stack.pop();
                    
                    if (stack.empty())
                        break;
                }
                stack.push(node);
            }
        }
        
        while (!stack.empty()){
            outputNodes.push_back(stack.top());
            stack.pop();
        }
        
        reverse(outputNodes.begin(), outputNodes.end());
        inputNodes.assign(outputNodes.begin(), outputNodes.end());
    }
    
    Node* buildExpressionTree(vector<Node *> &nodes) {
        stack<Node *> stack;
        
        for (vector<Node *>::iterator it  = nodes.begin(); it<nodes.end(); it++) {
            Node* node = *it;
            if (node->payload == TERM)
                stack.push(node);
            else {
                node -> right = stack.top();
                stack.pop();
                node -> left = stack.top();
                stack.pop();
                stack.push(node);
            }
        }
        return stack.top();
    }
   
    Scanner _scanner;
    int _currentToken;
    vector<Term *> _terms;
    Node *_expressionTree;
    int _termsContexStartPosition = 0;
    stack<Expression*> _expStack;
};

#endif

