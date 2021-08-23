
#ifndef STR_VIEW_H
#define STR_VIEW_H

#include "test.h"

namespace jomt::test
{   
    class TestStringView: public jomt::Test
    {


    public:

        TestStringView():jomt::Test(jomt::TestType::StringView){}
        ~TestStringView(){}

        void doTest();
    }; //class TestStringView

}//namespace jomt::test

#endif