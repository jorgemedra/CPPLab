#ifndef LAMBDAS_H
#define LAMBDAS_H
#pragma once

#include "test.h"

namespace jomt::test
{
    class LambdaTest: public jomt::Test
    {
        int _globalValue;

    public:
        LambdaTest(): 
            jomt::Test(jomt::TestType::Lambda), _globalValue{33}{}

        void doTest();

        void testByCopy();
        void testByReference();
        void testByThis();
        void testByMix();
        

    };

} // namespace jomt::test


#endif
