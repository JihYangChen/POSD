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
                
                vector<Term*> structArgs = getArgs();
                if(_scanner.nextToken() != ')')
                    throw string("unexpected token");
                return new Struct(*atom, structArgs);
            }
            else {
                _scanner.positionBackward();
                return atom;
            }
        }
        
        // Create List
        else if (token == '[') {
            vector<Term *> listArgs = getArgs();
            if(_scanner.nextToken() != ']')
                throw string("unexpected token");
            return new List(listArgs);
        }
        
        
        return nullptr;
    }
    
    // Return a vector of arguments, after calling the right parentheses and square brackets will NOT be discarded(nextToken will be ')' or ']').
    vector<Term*> getArgs()
    {
        vector<Term*> args = {};
        Term* term = createTerm();
        if (term) {
            args.push_back(term);
            while (_scanner.currentChar() == ',') {
                _scanner.nextToken();
                args.push_back(createTerm());
            }
        }
        // Empty Struct or List
        else {
            _scanner.positionBackward();
        }
        
        return args;
    }
    
    
    
private:
    Scanner _scanner;
};
#endif
