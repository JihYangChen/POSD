#include <gtest/gtest.h>
#include "utProxy.h"
#include "utStruct.h"
#include "utList.h"
#include "utScanner.h"
#include "utParser.h"
#include "utIterator.h"
#include "utExpression.h"
#include "utShell.h"
#include "utShellException.h"

#include <iostream>
#include <sstream>
#include <regex>
using namespace std;

int main( int argc , char **argv )
{
    string input;
    stringstream ss;
    
    auto isMatchHalt = [&]() {
        return regex_search(input, regex("^halt\\.$"));
        
    };
    
    auto isEndOfClause = [&]() {
        return regex_search(input, regex( "\\.$" ));
    };
    
    auto tryExexute = [](string clause) {
        Scanner s(clause);
        Parser p(s);
        try {
            p.buildExpression();
            string result = p.getResult();
            cout << result << endl;
        }
        catch (std::string &msg) {
            cout << msg << endl;
        }
    };
    
    for (cout << "?-", getline(cin, input); !isMatchHalt(); cin >> input)
    {
        if (isEndOfClause())
        {
            ss << input;
            tryExexute(ss.str());
            ss = stringstream();
            cout << "?-";
        }
        else
        {
            ss << input;
            cout << "| ";
        }
    }
    cout << "exit" << endl;
    
    return 0;
}


