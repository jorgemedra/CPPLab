
#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include "test.h"

namespace jomt::test
{
    class TestMatrix: public jomt::Test
    {
        void test_1();
        void test_2();
        void test_3();
        void test_4();

    public:
        TestMatrix() : jomt::Test(jomt::TestType::Matrix) {}
        ~TestMatrix() {}

        void doTest();

            
    };
}

#endif
