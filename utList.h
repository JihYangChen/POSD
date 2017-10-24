#ifndef UTLIST_H
#define UTLIST_H

using std::string;
using std::vector;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"


// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
    List list;
    EXPECT_EQ("[]", list.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
    Number num_8128(8128);
    vector<Term *> vector = {&num_8128};
    List list(vector);
    EXPECT_EQ("[8128]", list.symbol());
    EXPECT_EQ("[8128]", list.value());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
    Atom terence_tao("terence_tao");
    Atom alan_mathison_turing("alan_mathison_turing");
    vector<Term *> v = {&terence_tao, &alan_mathison_turing};
    List list(v);
    EXPECT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
    EXPECT_EQ("[terence_tao, alan_mathison_turing]", list.value());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
    Variable X("X");
    Variable Y("Y");
    vector<Term *> v = {&X, &Y};
    List list(v);
    EXPECT_EQ("[X, Y]", list.symbol());
    EXPECT_EQ("[X, Y]", list.value());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Number num_496(496);
    Variable X("X");
    Atom terence_tao("terence_tao");
    Atom tom("tom");
    vector<Term *> v = {&num_496, &X, &terence_tao};
    List list(v);
    EXPECT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
    Number num_496(469);
    Number num_8128(8128);
    Variable X("X");
    Atom terence_tao("terence_tao");
    Atom tom("tom");
    vector<Term *> v = {&num_496, &X, &terence_tao};
    List list(v);
    EXPECT_FALSE(num_8128.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
    Number num_496(496);
    Atom terence_tao("terence_tao");
    Variable X("X");
    vector<Term *> v1 = {&X};
    vector<Term *> v2 = {&num_496, &X, &terence_tao};
    Struct s(Atom("s"), v1);
    List list(v2);
    EXPECT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
    Number num_496(496);
    Atom terence_tao("terence_tao");
    Variable X("X");
    Variable Y("Y");
    vector<Term *> v = {&num_496, &X, &terence_tao};
    List list(v);
    EXPECT_TRUE(Y.match(list));
}

// ?- X = [496, X, terence_tao].
// true.
TEST(List, matchToVarOccuredInListShouldFail) {
    Number num_496(496);
    Atom terence_tao("terence_tao");
    Variable X("X");
    vector<Term *> v = {&num_496, &X, &terence_tao};
    List list(v);
    EXPECT_TRUE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
    Number num_496(496);
    Atom terence_tao("terence_tao");
    Variable X("X");
    vector<Term *> vector = {&num_496, &X, &terence_tao};
    List list(vector);
    EXPECT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
    Number num_496(496);
    Atom terence_tao("terence_tao");
    Variable X("X");
    Variable Y("Y");
    vector<Term *> v1 = {&num_496, &X, &terence_tao};
    vector<Term *> v2 = {&num_496, &Y, &terence_tao};
    List list1(v1);
    List list2(v2);
    EXPECT_TRUE(list1.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
    Number num_496(496);
    Number num_8128(8128);
    Atom terence_tao("terence_tao");
    Variable X("X");
    vector<Term *> v1 = {&num_496, &X, &terence_tao};
    vector<Term *> v2 = {&num_496, &num_8128, &terence_tao};
    List list1(v1);
    List list2(v2);
    EXPECT_TRUE(list1.match(list2));
    EXPECT_EQ("8128", X.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
    Number num_496(496);
    Atom terence_tao("terence_tao");
    Atom alan_mathison_turing("alan_mathison_turing");
    Variable X("X");
    Variable Y("Y");
    vector<Term *> v = {&num_496, &X, &terence_tao};
    List list(v);
    EXPECT_TRUE(Y.match(list));
    EXPECT_TRUE(X.match(alan_mathison_turing));
    EXPECT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
    EXPECT_EQ("alan_mathison_turing", X.value());
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    
    EXPECT_EQ(string("first"), l.head()->symbol());
    EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List l(args);
    
    EXPECT_EQ(string("second"), l.tail()->head()->value());
    EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching3) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> v1 = {&f};
    List list1(v1);
    vector<Term *> v2 = {&list1, &s, &t};
    List list2(v2);
    
    EXPECT_EQ("[first]", list2.head()->value());
    EXPECT_EQ("[second, third]", list2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
    Atom f("first"), s("second"), t("third");
    vector<Term *> args = {&f, &s, &t};
    List list(args);
    
    Variable H("H");
    Variable T("T");
    
    EXPECT_TRUE(H.match(*(list.tail()->tail()->head())));
    EXPECT_TRUE(T.match(*(list.tail()->tail()->tail())));
    EXPECT_EQ("third", H.value());
    EXPECT_EQ("[]", T.value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
    vector<Term *> args;
    List list(args);
    
    try {
        list.head();
    }
    catch (string str) {
        EXPECT_EQ("Accessing head in an empty list", str);
    }
}

// Given there is a empty list
// When client still want to get the tail of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
    vector<Term *> args;
    List list(args);
    
    try {
        list.tail();
    }
    catch (string str) {
        EXPECT_EQ("Accessing tail in an empty list", str);
    }
}

#endif
