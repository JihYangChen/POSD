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

    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;

    return 0;
}

