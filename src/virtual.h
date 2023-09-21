
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
        ~TestParent();

        virtual void allocByPublic();
        #ifdef MY_OWN_MACRO_NOT_DECLARED
        void myNotDeclaredFunction();
        #endif
        virtual void allocBySecond();
        //virtual void myInterfazToBeImplemented() = 0;

        void alloc();

        const std::string& name(){return _name;};
    };

    class TestChild: public TestParent
    {
        char* strChild;
        
        public:

        //TestChild(std::string name):TestParent(name),strChild{nullptr}{};
        TestChild(std::string name);
        ~TestChild();

        void allocBySecond() override;
        //void allocByPublic() override;
        //void myInterfazToBeImplemented() override;

        void alloc();
    };


    class Base{
    
    public:
        Base(std::string name); //IT's NOT POSSIBLE TO SET A VIRUTAL CONTRUCTOR
        // THIS VIRTUAL DESTRUCTOR ENSURE TO INVOKE 
        // THE RIGHT CONSTRCTOR IN THE CORRECT ORDER
        virtual ~Base(); 
        
    protected:
        std::string _name;

    };

    class Derived : public Base{
    public:
        Derived(std::string name);
        ~Derived();
    public:
        void test();
    };


    class TestVirtual: public Test
    {
        public:

            TestVirtual():Test(TestType::Virutal){};            
            void doTest();
            void testByPtr(TestParent* entity);
            
    };

}

#endif