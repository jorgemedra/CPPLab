
#include <iostream>
#include "const.h"


using namespace jomt::test;

void TestConst::doTest()
{
    setValue(10);
    std::cout   << "\tUsing setValue(int value)\n"
                << readValue() << "\n";

    setString("My String");

    std::cout   << "\tUsing setString('My String')\n"
                << readString() << "\n";
    
    //readString().push_back('.'); //Not Allowed by "const string"
}

void TestConst::setValue(int value)
{
    _myValue = value;
}

void TestConst::setString(std::string value)
{
    _myStr = value;
}

int TestConst::readValue() const
{
    std::cout << "\tint TestConst::readValue() const\n\t";
    return _myValue;
}

const std::string& TestConst::readString() const 
{   
    std::cout << "\tconst std::string& TestConst::readString() const\n\t";
    return _myStr;
}