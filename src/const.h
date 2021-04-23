
#ifndef CONST_H
#define CONST_H

#include "test.h"

namespace jomt::test
{

    class TestConst: public jomt::Test
    {
        
        int _myValue;
        std::string _myStr;

    public:
        
        TestConst(): Test(jomt::TestType::Consts){}
        ~TestConst(){}

        void doTest();

        void setValue(int);
        void setString(std::string);
        int readValue() const;
        const std::string& readString() const;
        
    };

}

#endif