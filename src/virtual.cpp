#include "virtual.h"
#include <iostream>

using namespace jomt::test;

TestParent::TestParent(std::string name):_name{name},strParent{nullptr}
{
    std::cout << "<-" << _name << "->TestParent()\n";
};

TestParent::~TestParent()
{
    std::cout << "<-" << _name << "->~TestParent\n";

    if(strParent == nullptr)
        delete[] strParent;
}

#ifdef MY_OWN_MACRO_NOT_DECLARED
void TestParent::myNotDeclaredFunction()
{
    std::cout << "<-" << _name << "-> TestParent::myNotDeclaredFunction()\n";
}
#endif

void TestParent::allocBySecond()
{
    std::cout << "<-" << _name << "->\t TestParent::allocBySecond\n";
    if(strParent == nullptr)
        strParent = new char[10];
}

void TestParent::allocByPublic()
{
    std::cout << "<-" << _name << "->\t TestParent::allocByPublic\n";
    if(strParent == nullptr)
        strParent = new char[10];
}

void TestParent::alloc()
{
    std::cout << "<-" << _name << "-> TestParent::alloc\n";
    allocByPublic();
    allocBySecond();
    
    /** IT'S NOT POSSIBLE IT MUS BE DECLARED **
    std::cout << "<-" << _name << "-> TestParent::alloc??????????\n";
    myNotDeclaredFunction();
    */

}

TestChild::TestChild(std::string name):TestParent(name),strChild{nullptr}{
    std::cout << "<-" << _name << "->\tTestChild()\n";
}

TestChild::~TestChild()
{    
    std::cout << "<-" << _name << "->\tTestChild::~TestChild\n";
    if(strChild == nullptr)
        delete[] strChild;
}

void TestChild::allocBySecond()
{
    std::cout << "<-" << _name << "->\t TestChild::allocByPrivate\n";
    if(strChild == nullptr)
        strChild = new char[10];
}

// void TestChild::allocByPublic()
// {
//     std::cout << "<-" << _name << "->\t TestChild::allocByPublic\n";
//     if(strChild == nullptr)
//         strChild = new char[10];
// }
    
void TestChild::alloc()
{
    std::cout << "<-" << _name << "-> TestChild::alloc\n";
    allocByPublic();
    allocBySecond();
    /** IT'S NOT POSSIBLE IT MUS BE DECLARED **
    std::cout << "<-" << _name << "-> TestChild::myNotDeclaredFunction??????????\n";
    myNotDeclaredFunction();
    */
}

/*
void TestChild::myInterfazToBeImplemented()
{
    std::cout << "<-" << _name << "-> TestChild::myInterfazToBeImplemented\n";
}
*/

//***************************

Base::Base(std::string name)
{
    std::cout << "Base(...)\n";
    _name = name;
}

Base::~Base()
{
    std::cout << "virtual ~Base()\n";
}

Derived::Derived(std::string name) : Base(name)
{
    std::cout << "\tDerived(" << _name << ")\n";
}

Derived::~Derived()
{
    std::cout << "\t~Derived\n";
}

void Derived::test()
{
    std::cout << "Derived::test\n";
}

//***************************


void TestVirtual::testByPtr(TestParent* entity)
{
    std::cout << "<-" << entity->name()  << "-> TestVirtual::testByPtr\n";
    std::cout << "\t:: IN THIS CASE, ANY INHERITED WHICH HAVE OVERRIDED\n"
              << "\t:: THE METHOD 'alloc()' will be affected due the methd\n"
              <<  "\t:: INVOKED IS FROM THE BASE(TestParent) class.\n"
              <<  "\t:: To Fix It declare alloc() as a 'virutal' method.\n"
              <<  "\t:: from  'TestParent' class.\n";
    entity->alloc();
}



void TestVirtual::doTest()
{
    {
        std::cout << "\n--------------------------------------\n";
        std::cout << "\nTesting Parent:\n";
        TestParent parent("Parent");
        std::cout << ":::: Using the 'TestParent parent' ::::\n";
        parent.alloc();
        std::cout << ":::: Using 'TestParent* entity' on '&parent' ::::\n";
        testByPtr(&parent);
    }

    {
        std::cout << "\n--------------------------------------\n";
        std::cout << "\nTesting Child:\n";
        std::cout << "\nTesting Child:\n";
        TestChild child("Child");
        std::cout << ":::: Using the 'TestChild child' ::::\n";
        child.alloc();
        std::cout << ":::: Using 'TestParent* entity' on '&child' ::::\n";
        testByPtr(&child);
    }

    {
        std::cout << "\n--------------------------------------\n";
        std::cout << "\nTESTING VIRTUAL DESTRUCTOR\n";
        Derived der = std::string("Derived");
        der.test();
    }

    std::cout << "\n==================================\n";

}