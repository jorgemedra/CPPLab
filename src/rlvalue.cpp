
#include "rlvalue.h"

using namespace jomt::test;

int& RLValue::lValue()
{
    return _InternalValue;
}

int RLValue::rValue() const
{
    return _InternalValue;
}

/*
std::ostream& RLValue::operator<<(std::ostream& os)
{
    return os << "Idiomatic Operator '<<' - Right Value = " << _InternalValue;
}
*/


void TestRLValue::doTest()
{
    RLValue rlTest;
    std::cout << "\nCurrent Value: " << rlTest << "\n";

    std::cout << "\n\tUsing RValue (Temporal Value): rlTest.rValue(): " <<  rlTest.rValue() <<"\n";
    
    std::cout << "\nUsing LValue: rlTest.lValue()++\n";
    rlTest.lValue()++;
    std::cout << "\n\tValue after RValue: " << rlTest << "\n";


    std::cout << "\nUsing LValue: rlTest.lValue() = rlTest.rValue() + 5\n";
    rlTest.lValue() = rlTest.rValue() + 5;
    std::cout << "\n\tValue after RValue: " << rlTest << "\n";
}


/************
 * 
 * This function shows how to receive a LValue and how to return another RValue
 * 
 ***********/ 
std::ostream& jomt::test::operator<<(std::ostream& os, const RLValue& ref)
{
    return os << "Internal Right Value = " << ref.rValue();
}
