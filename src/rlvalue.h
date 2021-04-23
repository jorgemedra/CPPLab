
#ifndef RLVALUE_H
#define RLVALUE_H

#include "test.h"
#include <iostream>

namespace jomt::test
{

    class RLValue
    {   
        int _InternalValue;
    
    public:

        RLValue():_InternalValue{0}{}

        int& lValue();
        int rValue() const;

        //std::ostream& operator<<(std::ostream&);
        RLValue& operator+=(long);
        RLValue& operator+=(double);
    };


    class TestRLValue: public jomt::Test
    {
    
    public:

        TestRLValue():Test(TestType::LRValue){};
        void doTest();

    };

    std::ostream& operator<<(std::ostream&, const RLValue&);
}

#endif