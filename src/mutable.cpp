#include <iostream>
#include "mutable.h"

using namespace jomt::test;


void TestMutable::modMut() const
{
    printInfo("modMut Before");
    //_intValue++; //If you uncomment this line, it will raise an error due the const.
    _mutInt++;

    std::cout   << "\nmodWMut() const\n"
                << "\t_intValue++ IS NOT ALLOWED because it's inside a const function\n"
                << "\t_mutInt++ It's possible to modified due to mutable declaration.\n";
    printInfo("modMut After");
}

void TestMutable::notConst()
{
    printInfo("notConst Before");
    _intValue++;
    _mutInt++;

    std::cout   << "\nnotConst()\n"
                << "\t_contInt++ Allowed\n"
                << "\t_mutInt++ Allowed.\n";
    printInfo("notConst After");
}

void TestMutable::printInfo(std::string info) const
{
    std::cout   << "\n::: " << info
                << "\n_intValue = " << _intValue 
                << "\n_mutInt = " << _mutInt << "\n";
}

void TestMutable::doTest()
{
    std::cout << "Changin all values twice times: \n\n";
    notConst();
    notConst();

    std::cout << "Trying to change all values twice times: \n\n";
    modMut();
    modMut();
}