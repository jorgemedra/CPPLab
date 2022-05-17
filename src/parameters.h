#ifndef TESTPARAMS_H
#define TESTPARAMS_H

#include "test.h"
#include "custom.h"

namespace jomt::test
{
    class TestParameters : public jomt::Test
    {

        
    public:
        
        TestParameters() : Test(jomt::TestType::Params){}
        void doTest();
    };
}

#endif