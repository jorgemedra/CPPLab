
#include <iostream>
#include "metaprog.h"
#include "custom.h"

using namespace jomt::test;

/*
Struct to test 
*/
template<class T, size_t N>
struct Array_Type
{   
    using type = T;
    static const size_t Dimension = N;
};

template<int N>
struct ShortInteger
{
    using type = typename std::conditional< (N <=  sizeof(char)), char, short>::type;
    type x;
};

template <class K, class V, bool IsKey>
struct KeyValueSelect
{
    using type = typename std::conditional<IsKey, K, V>::type;
    type x;
};

void MetaTest::TestTypeFunc()
{
    std::cout << "********************************************\n"
              << "Metaprograming test: Type Func.\n"
              << "Type Func is a function that either takes at\n"
              << "least one type argument or produce at least one\n"
              << "type as a result.\n"
              << "********************************************\n";

    bool isPol{false};
    isPol = std::is_polymorphic<int>().value;
    std::cout << "\n\t std::is_polymorphic<int>() is:\t\t" << (isPol ? "true\n" : "false\n");

    isPol = std::is_polymorphic<DummyClass>().value;
    std::cout << "\t std::is_polymorphic<DummyClass>() is:\t\t" << (isPol ? "true\n" : "false\n");

    isPol = std::is_polymorphic<char>().value;
    std::cout << "\t std::is_polymorphic<char>() is:\t\t" << (isPol ? "true\n" : "false\n");

    isPol = std::is_polymorphic<Test>().value;
    std::cout << "\t std::is_polymorphic<Test>() is:\t\t" << (isPol ? "true\n" : "false\n");
    std::cout << "(*) Note: Class Test has a virtual method to be implemented, so Test is a Polymorphy class.\n";

    std::cout << "\n.......... Declaring a template and a constant \"template<class T, size_t N>\"\n";
    {
        using MArray = Array_Type<MetaTest, 666>;
        MArray::type x;
        constexpr size_t s = MArray::Dimension;

        std::cout << "\n\tSize of Array_Type<MetaTest, 666>,\n"
                     "\tusing Array_Type<MetaTest, 666>::Dimension\n"
                     "\tis: " << s << "\n";
    }

    std::cout << "\n.......... Using std::conditional<bool, type1, type2>\"\n";
    {
        typename ShortInteger<1>::type ia = 8;
        typename ShortInteger<3443>::type ib = 200;

        std::cout << "\tType of ia: " << typeid(ia).name() << "\n"
                  << "\tType of ib: " << typeid(ib).name() << "\n";


        typename KeyValueSelect<KeyClass, ValueClass, true>::type datak(333);
        std::cout << "\tType of datak: " << typeid(datak).name() << "\n";
        typename KeyValueSelect<KeyClass, ValueClass, false>::type datav("My Value");
        std::cout << "\tType of datav: " << typeid(datav).name() << "\n";
    }

}


template<typename T>
void checkType()
{
    std::cout << "\tConstructible: " << (std::is_constructible<T>::value ? "true" : "false") << "\n";
    std::cout << "\tDestructible: " << (std::is_destructible<T>::value ? "true" : "false") << "\n";
    std::cout << "\tAbstract: " << (std::is_abstract<T>::value ? "true" : "false") << "\n";
    std::cout << "\tArray: " << (std::is_array<T>::value ? "true" : "false") << "\n";
    std::cout << "\tClass: " << (std::is_class<T>::value ? "true" : "false") << "\n";
    std::cout << "\tPointer: " << (std::is_pointer<T>::value ? "true" : "false") << "\n";
    std::cout << "\tCopy Assignable: " << (std::is_copy_assignable<T>::value ? "true" : "false") << "\n";
    std::cout << "\tObject: " << (std::is_object<T>::value ? "true" : "false") << "\n";
    std::cout << "\tSwappable: " << (std::is_swappable<T>::value ? "true" : "false") << "\n";
}

void MetaTest::TestValidProperties()
{
    std::cout << "********************************************\n"
              << "Metaprograming test: Check Properties.\n"
              << "These, and others more, can be use to valid at compile time\n"
              << "if the data type apply, in example, for contructible.\n"
              << "********************************************\n";

    std::cout << "\nChecking [bool]\n";
    checkType<bool>();

    std::cout << "\nChecking [KeyClass]\n";
    checkType<KeyClass>();

    std::cout << "\nChecking [ValueClass]\n";
    checkType<ValueClass>();

    std::cout << "\nChecking [DummyClass]\n";
    checkType<DummyClass>();

    std::cout << "\nChecking [RestrictedClass]\n";
    checkType<RestrictedClass>();
}


void MetaTest::TestConditionals()
{
    std::cout << "********************************************\n"
              << "Metaprograming test: Conditionals.\n"              
              << "********************************************\n";

    {
        using T1 = typename std::conditional<true, TypeA,TypeB>::type;
        using T2 = typename std::conditional<false, TypeA, TypeB>::type;
        T1 t1{"My Name"};
        T2 t2{"My Name"};
        std::cout << t1  << "\n";
        std::cout << t2 << "\n";
    }
}

#pragma region ITERACTION_RECURSION

//  constexpr is always requiered to calculate on compiler time.
//  N the value great or equal than 0 to calculate factorial.
template <int N>
constexpr int fibonacci()
{
    return fibonacci<N - 1>() + fibonacci<N - 2>();
}

template <>
constexpr int fibonacci<1>()
{
    return 1;
}

template <>
constexpr int fibonacci<0>()
{
    return 0;
}



void MetaTest::TestIteratorAndRec()
{
    std::cout << "********************************************\n"
              << "Metaprograming test: Iterator and Recursion.\n"
              << "********************************************\n";

    int ifact = fibonacci<30>();
    std::cout << "\n\t fibonacci<30>() is:" << ifact << "\n";
}

#pragma endregion

#pragma region VARIADIC
//----- Select

//Defining select template and structure, which has limit elements accoring the template.
template <unsigned N, typename... Cases>
struct select;

template <unsigned N, typename T, typename... Cases>
struct select<N, T, Cases...>:select<N-1, Cases...>{};

template <typename T, typename... Cases>
struct select<0, T, Cases...>{
    using type = T;
};

template <unsigned N, typename... Cases>
using Select = typename select<N, Cases...>::type;

void MetaTest::TestVariadic()
{
    //Select<0, char, int, DummyClass, KeyClass> t1;
    //auto t1 = Select<1>::type;
    //std::cout << "\t" << typeid(t1).name() << "\n";

}

#pragma endregion

void MetaTest::doTest()
{
    //TestTypeFunc();
    //TestValidProperties();
    //TestConditionals();
    TestIteratorAndRec();
}