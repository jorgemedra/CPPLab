#include "lambdas.h"
#include <cstdio>

using namespace jomt::test;


/**********************************************************************
* https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture
**********************************************************************/

void LambdaTest::testByCopy()
{
    int localVar{0};

    std::cout << "\nLambdaTest::testByCopy: \n";

    auto myFun1 = [](int val){
        std::cout << "\nLambda Fun. By Copy: auto myFun1 = [](int val){}\n"
                << "\tval(Bef):" << val++ 
                << "\tval(Aft):" << val << "\n";
    };

    //It will capture, by copy, all the local variables
    auto myFun2 = [=](){
        int lmbVar = localVar;
        std::cout << "\nLambda Fun. By Copy: auto myFun2 = [=]()\n"
                << "\tval(Bef):" << lmbVar++ 
                << "\tval(Aft):" << lmbVar << "\n";
    };


    std::cout   << "\nint localVar{0};"
                << "\nmyFun1(localVar);";
    myFun1(localVar);

    std::cout   << "\nmyFun2()";
    myFun2();

}

void LambdaTest::testByReference()
{
    int localVar{0};

    std::cout << "\nLambdaTest::testByReference :\n";
    
    auto myFun1 = [&](){
        std::cout << "\nLambda Fun. By Reference: auto myFun1 = [&](){}\n"
                << "\tval(Bef):" << localVar++
                << "\tval(Aft):" << localVar << "\n";
    };

    auto myFun2 = [&](int x){
        std::cout << "\nLambda Fun. By Reference: auto myFun2 = [&](int x){}\n"
                << "\tval(Bef):" << localVar;
        localVar += x;
        std::cout << "\tval(Aft):" << localVar << "\n";
    };

    std::cout   << "\nint localVar{0};"
                << "\nmyFun1();";
    myFun1();

    std::cout   << "\nmyFun2(6)";
    myFun2(6);

    std::cout << "\nlocalVar= " << localVar << "\n";
}

void LambdaTest::testByThis()
{
    std::cout << "\nLambdaTest::testByThis :\n";
    
    auto myFun1 = [this](){
        std::cout << "\nLambda Fun. By This: auto myFun1 = [this](){{}\n"
                << "\tval(Bef):" << this->_globalValue++
                << "\tval(Aft):" << this->_globalValue << "\n";
    };

    
    std::cout   << "\nthis->_globalValue = 3;"
                << "\nmyFun1();";
    this->_globalValue = 3;
    myFun1();

    std::cout << "\nthis->_globalValue = " << this->_globalValue << "\n";
}

void LambdaTest::testByMix()
{
    int localVar{0};
    int localToRef{0};

    std::cout << "\nLambdaTest::testByMix :\n";
    
    auto myFun1 = [&localToRef, this](int cpVal){
        std::cout << "\nLambda Fun. By Mix: auto myFun1 = [&localToRef, this](int cpVal){}\n"
                << "\tlocalVal(Bef):" << cpVal++ << ", localToRef(Bef):" << localToRef++ << ", this->_globalValue(Bef):" << this->_globalValue++ << "\n"
                << "\tlocalVal(Aft):" << cpVal << ", localToRef(Aft):" << localToRef << ", this->_globalValue(Aft):" << this->_globalValue << "\n";
    };


    std::cout   << "\niint localVar{0};"
                << "\nint localToRef{0};"
                << "\n_globalValue = 4;"
                << "\nmyFun1();";

    _globalValue = 4;
    myFun1(localVar);

    std::cout   << "\nOUTPUT:\n"
        << "\tlocalVal:" << localVar << ", localToRef:" << localToRef << ", this->_globalValue:" << this->_globalValue << "\n";
}

void LambdaTest::doTest()
{
    testByCopy();
    testByReference();
    testByThis();
    testByMix();
}