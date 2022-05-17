
#include "tpair.h"
#include "custom.h"
#include <iostream>
#include <utility>
#include <memory>
#include <string>

using namespace jomt::test;


std::pair<int,ValueClass> return_pair(int x, ValueClass name)
{
    std::cout << "\n\treturn_pair...\n";
    return std::make_pair(x, name);
}

/**
 * @brief This secodn option is not recommended because the local isntane will be deleted
 * afeter the context of return_pair_inst ends, so, that memory is 
 * 
 * @param x 
 * @param name 
 * @return std::pair<int, ValueClass>&& 
 */
std::pair<KeyClass, ValueClass> return_pair_inst(KeyClass &&key, ValueClass &&name)
{
    std::cout << "\n\treturn_pair_inst...\n ";
    return std::forward<std::pair<KeyClass, ValueClass>>(std::pair<KeyClass, ValueClass>(key, name));    
}

/**
 * @brief This first test shows how to return a pair and cast it
 * in differetns ways.
 */
void TestPair::test1()
{
    std::cout << "*********************************************************\n";
    std::cout << "Test 1. retruning std::pair<V,U>\n";

    { //Begin of Context 1        
        std::cout << "\n..................................................\n"
                << "\ncase 1.1, Getting a copy from function return_pair\n"
                << "\tstd::pair<int, std::string> ret_v = return_pair()\n";

        int int_value{33};
        ValueClass m_value{"My string 1"};

        std::pair<int, ValueClass> pv = return_pair(int_value, m_value);

        std::cout << "\t pv.first :[" << pv.first << "]\n";
        std::cout << "\t pv.second :[" << pv.second << "]\n";

        std::cout << "\n..................................................\n"
                  << "\ncase 1.2, Getting a copy from function return_pair\n"
                  << "\tauto [x, v] = return_pair\n";

        auto [x, v] = return_pair(27, {"X-My Second Value"});

        std::cout << "\t x :[" << x << "]\n";
        std::cout << "\t v :[" << v << "]\n";

        std::cout << "\t-- . -- . -- . -- . -- . --\n";
    } //End of Context 1

    { //Begin of Context 2        
        std::cout << "\n..................................................\n"
                  << "\ncase 2, Getting the same object instateaded into return_pair_inst, optimizing memory\n"
                  << "\tstd::pair<int, std::string> ret_v = return_pair_inst()\n";

        KeyClass m_key{36};
        ValueClass m_value{"My string 2"};

        std::pair<KeyClass, ValueClass> pv = return_pair_inst(std::forward<KeyClass>(m_key), std::forward<ValueClass>(m_value));

        std::cout << "\n\t m_key :[" << m_key.value() << "]\n";
        std::cout << "\t m_value  :[" << m_value.value() << "]\n";

        std::cout << "\t pv.first :[" << pv.first.value() << "]\n";
        std::cout << "\t pv.second :[" << pv.second.value() << "]\n";

        std::cout << "\t-- . -- . -- . -- . -- . --\n";
    } //End of Context 2

    { //Begin of Context 3
        std::cout << "\n..................................................\n"
                  << "\ncase 3, Creasting instance with special constructor\n"
                  << "\tpair( std::piecewise_construct_t, std::tuple<Args1...> first_args, std::tuple<Args2...> second_args)\n ";
            int m_key = 69;
        std::string m_value = "My Value 3";

        std::pair<KeyClass, ValueClass> pv(std::piecewise_construct, 
                                            std::tuple(m_key),
                                            std::tuple(m_value)
                                        );

        std::cout << "\n\t m_key :[" << m_key << "]\n";
        std::cout << "\t m_value  :[" << m_value << "]\n";

        std::cout << "\t pv.first :[" << pv.first.value() << "]\n";
        std::cout << "\t pv.second :[" << pv.second.value() << "]\n";
        std::cout << "\t-- . -- . -- . -- . -- . --\n";
    } //End of Context 3

   
    std::cout << "Test 1 ended\n";
}

void TestPair::test2()
{
    std::cout << "*********************************************************\n";
    std::cout << "Test 2. Creating an object from a tuple\n";

    std::cout << "\n..................................................\n"
              << "\nThis sample shows how to create a class from a typle\n"
              << "using the function std::make_from_tuple<T>::value, which is\n"
              << "available from C++17\n";

    auto info = std::make_tuple("My Name", "45", false);
    DummyClass dummy = std::make_from_tuple<DummyClass>(info);

    std::cout << "DummyClass: " << dummy << "\n";
    std::cout << "\t-- . -- . -- . -- . -- . --\n";
}

void TestPair::test3()
{
    std::cout << "*********************************************************\n";
    std::cout << "Test 3. Receving a Tupple from a lambda function\n";

    std::cout << "\n..................................................\n"
              << "\nauto[m_str, m_int, m_key, m_value] = getTuple();\n";

    auto getTuple = []() {
        return std::make_tuple("MyString", 2341, KeyClass(788),ValueClass("My Value"));
    };

    auto[m_str, m_int, m_key, m_value] = getTuple();

    std::cout << "m_str: " << m_str << "\n";
    std::cout << "m_int: " << m_int << "\n";
    std::cout << "m_key: " << m_key << "\n";
    std::cout << "m_vakue: " << m_value << "\n";
    std::cout << "\t-- . -- . -- . -- . -- . --\n";
}

void TestPair::doTest()
{
    test1();
    test2();
    test3();
}