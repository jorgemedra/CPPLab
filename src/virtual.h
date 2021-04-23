
#ifndef VIRTUAL_H
#define VIRTUAL_H

#include "test.h"

namespace jomt::test
{
    class TestParent
    {
        char* strParent;
        
        protected:
        std::string _name;
        
        public:

        //TestParent(std::string name):_name{name},strParent{nullptr}{};
        TestParent(std::string name);
        virtual ~TestParent();

        virtual void allocByPublic();
        virtual void allocBySecond();
        void alloc();
    };

    class TestChild: public TestParent
    {
        char* strChild;
        
        public:

        //TestChild(std::string name):TestParent(name),strChild{nullptr}{};
        TestChild(std::string name);
        ~TestChild();

        void allocByPublic();
        //void allocBySecond();
        void alloc();
    };

    class TestVirtual: public Test
    {
        public:

            TestVirtual():Test(TestType::Virutal){};
            void doTest();
    };

}

#endif