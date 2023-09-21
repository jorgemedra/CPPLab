#ifndef DUMPL_H
#define DUMPL_H

#include "test.h"
namespace jomt::test
{
    class TestDump: public jomt::Test
    {
        void raise_an_exception();
    public:

        TestDump():Test(jomt::TestType::Dump){}
        void doTest();
    };
}

#endif