#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"

class Parser{
public:
    Parser(Scanner scanner) : _scanner(scanner){}
    Term* createTerm(){
        int token = _scanner.nextToken();
        if(token == VAR){
            return new Variable(symtable[_scanner.tokenValue()].first);
        }
        else if (token == NUMBER){
            return new Number(_scanner.tokenValue());
        }
        else if (token == ATOM){
            Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
            
            int nextToken = _scanner.nextToken();
            if(nextToken == '(') {
                vector<Term*> structArgs = getArgs();
                if(_currentToken == ')')
                    return new Struct(*atom, structArgs);
            }
            if (nextToken == ')')
                _scanner.positionBackward();
            return atom;
        }
        
        return NULL;
    }
    
    vector<Term*> getArgs()
    {
        Term* term = createTerm();
        vector<Term*> args;
        if(term) {
            args.push_back(term);
        }
        while((_currentToken = _scanner.nextToken()) == ',') {
            args.push_back(createTerm());
        }
        return args;
    }
    
    
    
//private:
    Scanner _scanner;
    int _currentToken;
};
#endif
