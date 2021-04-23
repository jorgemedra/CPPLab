
#include "pointer.h"
#include <iostream>

using namespace jomt::test;


void TestPointer::printInfo(std::string info, int value)
{
    std::cout   << "\n" << info << "\n";
    std::cout << "\tAddress: " << &value << "\n";
    std::cout << "\tValue: " << value << "\n";
    std::cout   << "\n";
}

void TestPointer::printInfo(std::string info, int *value)
{
    std::cout   << "\n" << info << "\n";
    std::cout << "\tAddress: " << value << "\n";
    std::cout << "\tValue: " << *value << "\n";
    std::cout   << "\n";
}

void TestPointer::doTest()
{
    int myInt = 5;
    printInfo("int myInt = 5", myInt);    

    int *pInt = &myInt;
    printInfo("int *pInt = &myInt", pInt);

    int *pInt2 = pInt;
    printInfo("int *pInt2 = pInt", pInt2);

    *pInt2 = *pInt2 +1;
    printInfo("*pInt2 = *pInt2 +1", pInt2);
    printInfo("*pInt", pInt);

    int *pInt3 = new int(*pInt2);
    printInfo("int *pInt3 = new int(*pInt2)", pInt3); 

    (*pInt3)++;
    printInfo("(*pInt3)++", pInt3); 
    printInfo("*pInt", pInt);
    
    delete pInt3; 
}