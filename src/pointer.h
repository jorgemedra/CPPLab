
#ifndef POINTER_H
#define POINTER_H

#include "test.h"

namespace jomt::test
{
    class TestPointer: public jomt::Test
    {
        void printInfo(std::string, int);
        void printInfo(std::string, int*);

    public:

        TestPointer():Test(jomt::TestType::Pointers){}
        void doTest();
    };
}

#endif
