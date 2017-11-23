#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "node.h"

class Parser{
public:
    Parser(Scanner scanner) : _scanner(scanner){}
    Term* createTerm(){
        int token = _scanner.nextToken();
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
        _expressionTree = createExpressionTree();
    }
    
    Node * expressionTree() {
        return _expressionTree;
    }
   
    
    

private:
    FRIEND_TEST(ParserTest, createArgs);
    FRIEND_TEST(ParserTest,ListOfTermsEmpty);
    FRIEND_TEST(ParserTest,listofTermsTwoNumber);
    FRIEND_TEST(ParserTest, createTerm_nestedStruct3);
    
    Term * createStructure(Atom & structName) {
        int startIndexOfStructArgs = (int)_terms.size();
        createTerms();
        
        if(_scanner.nextToken() != ')')
            throw string("unexpected token");
        
        vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
        _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
        
        return new Struct(structName, args);
    }
    
    Term * createList() {
        int startIndexOfListArgs = (int)_terms.size();
        createTerms();
        
        if(_scanner.nextToken() != ']')
            throw string("unexpected token");
        
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
    
    Node* createExpressionTree() {
        Node *leftSubTree = createSubTree();
        
        if (!leftSubTree)
            return nullptr;
        else {
            int conjunctionOperator;
            Node *conjunctionNode = nullptr;
            if ((conjunctionOperator =_scanner.nextToken()) != ATOMSC) {
                if (conjunctionOperator == ',')
                    conjunctionNode = new Node(COMMA);
                else if (conjunctionOperator == ';'){
                    conjunctionNode = new Node(SEMICOLON);
                    _termsContexStartPosition = (int)_terms.size();
                }
                Node *rightSubTree = createExpressionTree();
                
                conjunctionNode -> left = leftSubTree;
                conjunctionNode -> right = rightSubTree;
                
                return conjunctionNode;
            }
            else
                return leftSubTree;
        }
    }
    
    Node* createSubTree() {
        Term *leftTerm = createTerm();
        if(!leftTerm)
            return nullptr;
        _terms.push_back(leftTerm);
        
        int midNodeToken = _scanner.nextToken();
        Term *rightTerm = createTerm();
        _terms.push_back(rightTerm);
        
        Node *leftNode = new Node(TERM, leftTerm, nullptr, nullptr);
        Node *rightNode = new Node(TERM, rightTerm, nullptr, nullptr);
        
        if (midNodeToken == '=') {
            Node *midNode = new Node(EQUALITY, nullptr, leftNode, rightNode);
            _expressionTree = midNode;
            return midNode;
        }
        else
            return nullptr;
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
   
    Scanner _scanner;
    vector<Term *> _terms;
    Node *_expressionTree;
    int _termsContexStartPosition = 0;
};
#endif

