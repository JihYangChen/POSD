#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "iterator.h"

// s(1, t(X, 2), Y)
TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term *> *itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

// s(1, t(X, 2), Y)
TEST(iterator, nested_iterator) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term *> *itStruct1 = s.createIterator();
    
    itStruct1->first();
    ASSERT_EQ("1", itStruct1->currentItem()->symbol());
    
    itStruct1->next();
    Iterator<Term *> *itStruct2 = itStruct1->currentItem()->createIterator();
    itStruct2->first();
    ASSERT_EQ("X", itStruct2->currentItem()->symbol());
    itStruct2->next();
    ASSERT_EQ("2", itStruct2->currentItem()->symbol());
    itStruct2->next();
    ASSERT_TRUE(itStruct2->isDone());
    itStruct1->next();
    ASSERT_EQ("Y", itStruct1->currentItem()->symbol());
    itStruct1->next();
    ASSERT_TRUE(itStruct1->isDone());
}

// [1, t(X, 2), Y]
TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term *> *itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
    Number one(1);
    Iterator<Term *> * nullIterator = one.createIterator();
    nullIterator->first();
    ASSERT_TRUE(nullIterator->isDone());
}

// s(1, t(X, 2), Y)
TEST(iterator, structDFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term *> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

// s(1, t(X, 2, [X, Y]), Y)
TEST(iterator, structDFSwithList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    List l({&X,&Y});
    Struct t(Atom("t"), { &X, &two,&l });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term *> *it = s.createDFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(X, 2, [X, Y])", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}


// [2, [X, Y, 1, 2], X]
TEST(iterator, listDFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    List l({&X,&Y,&one,&two});
    List l2({&two,&l,&X});
    Iterator<Term *> *it = l2.createDFSIterator();
    it->first();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[X, Y, 1, 2]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

// [X, Y, t(X, 2), []]
TEST(iterator, ListDFSwithStruct) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l2;
    List l({&X,&Y, &t, &l2});
    Iterator<Term *> *it = l.createDFSIterator();
    it->first();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[]", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

// s(1, t(X, 2), Y)
TEST(iterator, StructBFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term *> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

// s(1, t(X, 2, [X, Y]), Y)
TEST(iterator, structBFSwithList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    List l({&X,&Y});
    Struct t(Atom("t"), { &X, &two,&l });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term *> *it = s.createBFSIterator();
    it->first();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(X, 2, [X, Y])", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

//[2, [X, Y], 1]
TEST(iterator, listBFS) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    List l({&X,&Y});
    List l2({&two,&l,&one});
    Iterator<Term *> *it = l2.createBFSIterator();
    it->first();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[X, Y]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("1", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

// [X, Y, t(X, 2), []]
TEST(iterator, ListBFSwithStruct) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l2;
    List l({&X,&Y, &t, &l2});
    Iterator<Term *> *it = l.createBFSIterator();
    it->first();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("Y", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("t(X, 2)", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("[]", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("X", it->currentItem()->symbol());
    it->next();
    ASSERT_EQ("2", it->currentItem()->symbol());
    it->next();
    ASSERT_TRUE(it->isDone());
}

#endif

