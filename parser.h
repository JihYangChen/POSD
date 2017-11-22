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
        
        // Create Variable
        if(token == VAR){
            return new Variable(symtable[_scanner.tokenValue()].first);
        }
        
        // Create Number
        else if (token == NUMBER){
            return new Number(_scanner.tokenValue());
        }
        
        // Create Atom or Struct
        else if (token == ATOM || token == ATOMSC){
            Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
            
            // Create Struct
            if(_scanner.nextToken() == '(') {
                return createStructure(*atom);
            }
            // Create Atom
            else {
                _scanner.positionBackward();
                return atom;
            }
        }
        
        // Create List
        else if (token == '[') {
            return createList();
        }
        
        return nullptr;
    }
    
    vector<Term*> getTerms() {
        return _terms;
    }
    
    void matchings() {
        createExpressionTree();
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
    
    void createExpressionTree() {
        Node *leftSubTree = createSubTree();
        
        if (!leftSubTree)
            _expressionTree = nullptr;
        else {
            int conjunctionOperator;
            Node *conjunctionNode = nullptr;
            while ((conjunctionOperator =_scanner.nextToken()) != ATOMSC) {
                Node *rightSubTree = createSubTree();
                
                if (conjunctionOperator == ',')
                    conjunctionNode = new Node(COMMA, nullptr, leftSubTree, rightSubTree);
                else if (conjunctionOperator == ';')
                    conjunctionNode = new Node(SEMICOLON, nullptr, leftSubTree, rightSubTree);
                
                leftSubTree = conjunctionNode;
                _expressionTree = conjunctionNode;
            }
        }
        
        
    }
    
    Node * createSubTree() {
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
    
    Scanner _scanner;
    vector<Term *> _terms;
    Node *_expressionTree;
};
#endif

