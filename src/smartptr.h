
#ifndef SMARTPTR_H
#define SMARTPTR_H

#include "test.h"
#include <iostream>

namespace jomt::test
{

    class MemDummy
    {
        char* buffer;
        std::string _name;
    public:

        MemDummy(std::string name):_name{name}
        {
            std::cout << "[" << _name << "] MemDummy\n";
            buffer = new char[1024];
        }

        ~MemDummy()
        {
            std::cout << "[" << _name << "] ~MemDummy\n";
            delete[] buffer;
        }

        void printInfo();

    };

    class TestSmartPtr: public jomt::Test
    {

    public:
        TestSmartPtr():jomt::Test(jomt::TestType::SmartPointer){}

        void doTest();

        void testUniqPrt();
        void testSharedPrt();
        void testWeakPrt();
    };
}



#endif