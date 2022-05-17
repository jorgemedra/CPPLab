
#ifndef TPAIR_H
#define TPAIR_H

#include "test.h"

namespace jomt::test
{




class TestPair: public Test
{

    void test1();
    void test2();
    void test3();

public:
    TestPair() : jomt::Test(jomt::TestType::Pair){}
    void doTest();
};

} //namespace

#endif