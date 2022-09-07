
#ifndef MAPS_H
#define MAPS_H

#include "test.h"
#include <string>
#include <iostream>

namespace jomt::test
{
    class MapTest: public jomt::Test
    {
        
        void test1();
        void test2();
        void test3();
        void test4();
        void test5();
        void test6();

    public:
        MapTest() : jomt::Test(jomt::TestType::Maps) {}
        //~MapTest() = default;

        void doTest();
    };
}//namespace

#endif
