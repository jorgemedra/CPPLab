
#ifndef CONSTEX_H
#define CONSTEX_H

#include "test.h"

namespace jomt::test
{

    class TestConstExpr: public jomt::Test
    {
        constexpr size_t factorial(size_t);

    public:
        TestConstExpr(): jomt::Test(jomt::TestType::ConstExpr){}
        ~TestConstExpr(){}

        void doTest();
    };

}


#endif