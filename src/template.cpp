
#include "template.h"
#include <iostream>

using namespace jomt::test;

void TestTemplate::setName(std::string name)
{
    _nameChild = name;
}

/*
void TestTemplate::name() const
{
    std::cout << "Child Name: "<< _nameChild ;
}
*/

std::ostream& jomt::test::operator<<(std::ostream& strm, const TestTemplate& t)
{
    return strm << "[Name: " << t._nameChild << ", Counter: " << t._counter << "]";
}

TestTemplate& TestTemplate::operator++(int x)
{
    _counter++;
    return *this;
}


void TestTemplate::doTest()
{
    setName("TestTemplate Inst");

    int x{23};
    char c{'c'};
    double d{3.1416335577};
    myFunOnTemplate<int, 230>(x);
    myFunOnTemplate<char, 44535>(c);
    myFunOnTemplate<double, 12>(d);


    MyTemplate<int> mtInt;
    mtInt.printIntoByCopy(x);
    mtInt.printIntoByPtr(&x);
    mtInt.printIntoByRef(x);

    myFunOnTemplate<int, 230>(x);

    MyTemplate<TestTemplate> mtTest;
    TestTemplate tX;
    tX.setName("Test X");

    mtTest.printIntoByCopy(tX);
    mtTest.printIntoByPtr(&tX);
    mtTest.printIntoByRef(tX);

    myFunOnTemplate<TestTemplate, 666>(tX);

}