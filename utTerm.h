#ifndef UTTERM_H
#define UTTERM_H

#include "variable.h"
#include "atom.h"
#include "Number.h"

//test Number.value()
TEST (Number,ctor) {
    Number _3(3);
    ASSERT_EQ("3", _3.value());
}
//test Number.symbol()
TEST (Number, symbol) {
    Number _80(80);
    ASSERT_EQ("80", _80.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
    Number _25(25);
    ASSERT_TRUE(_25.match(_25));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
    Number _25(25);
    Number _0(0);
    ASSERT_FALSE(_25.match(_0));
}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
    Number _25(25);
    Atom tom("tom");
    ASSERT_FALSE(_25.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
    Number _25(25);
    Var X("X");
    ASSERT_TRUE(_25.match(X));
}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
    Atom tom("tom");
    Number _25(25);
    ASSERT_FALSE(tom.match(_25));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
    Atom tom("tom");
    Var X("X");
    X.match(tom);
    ASSERT_EQ(X.value(), tom.symbol());
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
    Atom tom("tom");
    Var X("X");
    X.match(tom);
    tom.match(X);
    ASSERT_EQ(X.value(), tom.symbol());
}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
    Var X("X");
    Atom jerry("jerry");
    Atom tom("tom");
    X.match(jerry);
    ASSERT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST (Var, matchSuccessToNumber) {
    Var X("X");
    Number _5(5);
    ASSERT_TRUE(X.match(_5));
}

// ?- X=25, X= 100.
// false.
TEST (Var, matchFailureToTwoDiffNumbers) {
    Var X("X");
    Number _25(25);
    Number _100(100);
    X.match(_25);
    ASSERT_FALSE(X.match(_100));
}

// ?- X=tom, X= 25.
// false.
TEST (Var, matchSuccessToAtomThenFailureToNumber) {
    Var X("X");
    Atom tom("tom");
    Number _25(25);
    X.match(tom);
    ASSERT_FALSE(X.match(_25));
}
//?- tom=X, 25=X.
//false.
TEST (Var, matchSuccessToAtomThenFailureToNumber2) {
    Atom tom("tom");
    Var X("X");
    Number _25(25);
    tom.match(X);
    ASSERT_FALSE(_25.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Var, reAssignTheSameAtom){
    Var X("X");
    Atom tom("tom");
    X.match(tom);
    ASSERT_TRUE(tom.match(X));
}
#endif
