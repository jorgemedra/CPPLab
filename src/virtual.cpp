#include "virtual.h"
#include <iostream>

using namespace jomt::test;

TestParent::TestParent(std::string name):_name{name},strParent{nullptr}
{
    std::cout << "<-" << _name << "-> TestParent::TestParent()\n";
};

void TestParent::allocBySecond()
{
    std::cout << "<-" << _name << "-> TestParent::allocBySecond\n";
    if(strParent == nullptr)
        strParent = new char[10];
}

void TestParent::allocByPublic()
{
    std::cout << "<-" << _name << "-> TestParent::allocByPublic\n";
    if(strParent == nullptr)
        strParent = new char[10];
}

void TestParent::alloc()
{
    std::cout << "<-" << _name << "-> TestParent::alloc\n";
    allocByPublic();
    allocBySecond();
}

TestParent::~TestParent()
{
    std::cout << "<-" << _name << "-> TestParent::~TestParent\n";

    if(strParent == nullptr)
        delete[] strParent;
}




TestChild::TestChild(std::string name):TestParent(name),strChild{nullptr}{
    std::cout << "<-" << _name << "-> TestChild::TestChild()\n";
}

/*
void TestChild::allocBySecond()
{
    std::cout << "<-" << _name << "-> TestChild::allocByPrivate\n";
    if(strChild == nullptr)
        strChild = new char[10];
}
*/

void TestChild::allocByPublic()
{
    std::cout << "<-" << _name << "-> TestChild::allocByPublic\n";
    if(strChild == nullptr)
        strChild = new char[10];
}
    
void TestChild::alloc()
{
    std::cout << "<-" << _name << "-> TestChild::alloc\n";
    allocBySecond();
    allocByPublic();
}

TestChild::~TestChild()
{
    std::cout << "<-" << _name << "-> TestChild::~TestChild\n";
    if(strChild == nullptr)
        delete[] strChild;
}


void TestVirtual::doTest()
{
    std::cout << "\nTesting Parent:\n";
    {
        TestParent parent("Parent");
        parent.alloc();
    }


    std::cout << "\nTesting Child:\n";
    TestChild child("Child");
    child.alloc();

}