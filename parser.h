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
        else if (token == ATOM){
            Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
            
            // Create Struct
            if(_scanner.currentChar() == '(') {
                _scanner.nextToken();
                vector<Term*> structArgs = getArgs();
                return new Struct(*atom, structArgs);
            }
            else {
                return atom;
            }
        }
        
        // Create List
        else if (token == '[') {
            vector<Term *> listArgs = getArgs();
            return new List(listArgs);
        }
        
        // Create more term
        else if (token == ',') {
            return createTerm();
        }
        
        return NULL;
    }
    
    // Return a vector of arguments, after calling the right parentheses and square brackets will be discarded.
    vector<Term*> getArgs()
    {
        Term* term = createTerm();
        vector<Term*> args;
        if(term) {
            args.push_back(term);
            while(_scanner.nextToken() == ',') {
                args.push_back(createTerm());
            }
        }
        // Empty structure or list.
        /*
        else {
            _scanner.positionBackward();
        }
        else {
            while(_scanner.nextToken() == ',') {
                args.push_back(createTerm());
            }
        }
         */
        return args;
    }
    
    
    
//private:
    Scanner _scanner;
};
#endif
