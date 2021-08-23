#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <iostream>
#include "test.h"

namespace jomt::test
{


    /*
    Template always requires to be coded into the Header file.
    */   
    template <class T>
    class MyTemplate
    {
        
        public:

        void printIntoByCopy(T cv)
        {
            std::cout << "Template By Copy: " << cv << "\n";
        }

        void printIntoByPtr(const T* pv)
        {
            std::cout << "Template By Pointer: " << *pv << "\n";
        }

        void printIntoByRef(T& rv)
        {
            rv++;
            std::cout << "Template By Reference: " << rv << "\n";
        }
    
    };
    

    template<class T, int N>
    void myFunOnTemplate(T tp)
    {
        std::cout << "Info from T: " << tp << " and N = " << N << "\n";
    }


    template<class K, class T>
    class Parent
    {
        using key_type = K;
        using value_type = T;

    protected:
        key_type _key;
        value_type _value;

    public:
        Parent(key_type k, value_type v): _key{k}, _value{v}{}
        
        const key_type& Key(){return _key;}
        const value_type& Value(){return _value;}
    };

    template<class K, class T>
    class Child: public Parent<K,T>
    {   
        using key_type = K;
        using value_type = T;
        
    public:
        Child(key_type k, value_type v): Parent<K,T>(k,v){}

        Child operator++(int n){
            this->_value++;
            return *this;
        }
    };


    class TestTemplate: public jomt::Test
    {
        std::string _nameChild;
        size_t _counter;

        void testIhnerence();
    public:

        TestTemplate():  jomt::Test(jomt::TestType::Templates),
                        _nameChild{"-Uknown-"},_counter{0}{}
        
        ~TestTemplate(){}

        void doTest();
        void setName(std::string name);

        friend std::ostream& operator<<(std::ostream&, const TestTemplate&);
        TestTemplate& operator++(int x);
    };

    std::ostream& operator<<(std::ostream&, const TestTemplate&);
}

#endif