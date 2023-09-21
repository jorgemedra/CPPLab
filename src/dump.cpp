#include <string>
#include <iostream>
#include "dump.h"

using namespace jomt::test;

void TestDump::raise_an_exception()
{
    std::string myStr("1234");

    std::cout << "TestDump::raise_an_exception\n";   
    std::cout << "\t" << myStr << "\n";
    std::cout << "\t" << myStr[56] << "\n";
}

void TestDump::doTest()
{
    std::cout << "Executing a process that will raise an exception and crash the program.\n";
    raise_an_exception();
}