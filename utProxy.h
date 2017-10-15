
#ifndef utProxy_h
#define utProxy_h

#include "variable.h"
#include "atom.h"

TEST(Proxy, constructVariable) {
    Variable X("X");
    EXPECT_EQ("X", X.symbol());
    EXPECT_EQ("X", X.value());
}

// X = Y.
TEST(Proxy, matchVariable1) {
    Variable X("X");
    Variable Y("Y");
    EXPECT_TRUE(X.match(Y));
    EXPECT_EQ("X", X.symbol());
    EXPECT_EQ("Y", X.value());
    EXPECT_EQ("Y", Y.symbol());
    EXPECT_EQ("Y", Y.value());
}

// X = Y, Y = Z.
TEST(Proxy, matchVariable2) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Y.match(Z));
    EXPECT_EQ("Z", X.value());
    EXPECT_EQ("Z", Y.value());
    EXPECT_EQ("Z", Z.value());
}

// X = Y, Z = Y.
TEST(Proxy, matchVariable3) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Z.match(Y));
    EXPECT_EQ("Z", X.value());
    EXPECT_EQ("Z", Y.value());
    EXPECT_EQ("Z", Z.value());
}

// X = Y, Z = W, Y = Z.
TEST(Proxy, matchVariable4) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Variable W("W");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Z.match(W));
    EXPECT_TRUE(Y.match(Z));
    EXPECT_EQ("W", X.value());
    EXPECT_EQ("W", Y.value());
    EXPECT_EQ("W", Z.value());
    EXPECT_EQ("W", W.value());
}

// X = Y, Z = W, Y = Z, Y = tom.
TEST(Proxy, matchVariable5) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Variable W("W");
    Atom tom = Atom("tom");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Z.match(W));
    EXPECT_TRUE(Y.match(Z));
    EXPECT_TRUE(Y.match(tom));
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("tom", Y.value());
    EXPECT_EQ("tom", Z.value());
    EXPECT_EQ("tom", W.value());
}

// X = Y, Z = W, Y = tom, Y = Z.
TEST(Proxy, matchVariable6) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Variable W("W");
    Atom tom = Atom("tom");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Z.match(W));
    EXPECT_TRUE(Y.match(tom));
    EXPECT_TRUE(Y.match(Z));
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("tom", Y.value());
    EXPECT_EQ("tom", Z.value());
    EXPECT_EQ("tom", W.value());
}

// X = Y, Z = W, W = tom, Y = Z.
TEST(Proxy, matchVariable7) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Variable W("W");
    Atom tom = Atom("tom");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Z.match(W));
    EXPECT_TRUE(W.match(tom));
    EXPECT_TRUE(Y.match(Z));
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("tom", Y.value());
    EXPECT_EQ("tom", Z.value());
    EXPECT_EQ("tom", W.value());
}

// X = Y, Z = W, Y = Z, Y = tom, A = B, Y = B.
TEST(Proxy, matchVariable8) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Variable W("W");
    Variable A("A");
    Variable B("B");
    Atom tom = Atom("tom");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Z.match(W));
    EXPECT_TRUE(Y.match(Z));
    EXPECT_TRUE(Y.match(tom));
    EXPECT_TRUE(A.match(B));
    EXPECT_TRUE(Y.match(B));
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("tom", Y.value());
    EXPECT_EQ("tom", Z.value());
    EXPECT_EQ("tom", W.value());
    EXPECT_EQ("tom", A.value());
    EXPECT_EQ("tom", B.value());
}

// X = Y, Z = W, Y = tom, Z = jerry, X = W.
TEST(Proxy, matchVariable9) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Variable W("W");
    Atom tom = Atom("tom");
    Atom jerry = Atom("jerry");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Z.match(W));
    EXPECT_TRUE(Y.match(tom));
    EXPECT_TRUE(Z.match(jerry));
    EXPECT_FALSE(X.match(W));
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("tom", Y.value());
    EXPECT_EQ("jerry", Z.value());
    EXPECT_EQ("jerry", W.value());
}

// X = tom, Y = jerry, X = W.
TEST(Proxy, matchVariable10) {
    Variable X("X");
    Variable Y("Y");
    Atom tom = Atom("tom");
    Atom jerry = Atom("jerry");
    EXPECT_TRUE(X.match(tom));
    EXPECT_TRUE(Y.match(jerry));
    EXPECT_FALSE(X.match(Y));
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("jerry", Y.value());
}

// X = Y, Z = W, Y = tom, Z = tom, X = W.
TEST(Proxy, matchVariable11) {
    Variable X("X");
    Variable Y("Y");
    Variable Z("Z");
    Variable W("W");
    Atom tom = Atom("tom");
    EXPECT_TRUE(X.match(Y));
    EXPECT_TRUE(Z.match(W));
    EXPECT_TRUE(Y.match(tom));
    EXPECT_TRUE(Z.match(tom));
    EXPECT_TRUE(X.match(W));
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("tom", Y.value());
    EXPECT_EQ("tom", Z.value());
    EXPECT_EQ("tom", W.value());
}

// X = tom, Y = tom, X = Y.
TEST(Proxy, matchVariable12) {
    Variable X("X");
    Variable Y("Y");
    Atom tom = Atom("tom");
    EXPECT_TRUE(X.match(tom));
    EXPECT_TRUE(Y.match(tom));
    EXPECT_TRUE(X.match(Y));
    EXPECT_EQ("tom", X.value());
    EXPECT_EQ("tom", Y.value());
}

#endif /* utProxy_h */
