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
#include <regex>
using namespace std;

int main( int argc , char **argv )
{
//    string s1 = "adhhd+bcd*cd+dd+efd";
//    cout << s1 << endl;
//
//    regex reg("[\\w]+|[\\+\\*]");
//
//
//    smatch sm;

//    if (std::regex_match (s1,reg))
//        cout << "het" << endl;
    
//    if (regex_search(s1 , sm , reg)) {
//        cout << sm.size() << endl;
//        for (unsigned i=0; i<sm.size(); ++i) {
//            std::cout << "[" << sm[i] << "] ";
//        }
//    }
    
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}
