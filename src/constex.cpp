
#include "constex.h"
#include <iostream>
#include <chrono>

using namespace jomt::test;

constexpr size_t N = 10000;

void TestConstExpr::doTest()
{
    auto start = std::chrono::high_resolution_clock::now();
    const size_t rf = factorial(N);
    
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout   << "Using Constant Expression: \n"
                << "\nFactorial = " << rf << "\n";

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout <<"\n::Duration Const Expr: " << duration.count() << "::\n\n";

    std::cout << "............\n\n";
    
    size_t n;
    do{
        std::cout << "Press " << N << "\n>";
        std::cin >> n;
    }while(n != N);


    auto start2 = std::chrono::high_resolution_clock::now();
    size_t rf2 = factorial(n);
    auto stop2 = std::chrono::high_resolution_clock::now();

    std::cout   << "Using RunTime: \n"
                << "\nFactorialNE = " << rf2 << "\n";
    
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    std::cout <<"\n:: Duration of Runtime: " << duration2.count() << "::\n\n";
}


/**********************************************************************
 * This code will be calculate as long as the parameter n
 * gets an constant value, so it will be optimized by the compile,
 *  but, in the other side, it will be handled as a normal code.
 * 
 * If you wants to comapre with a non-recursive function, uncomment the 
 * code below and comment the other function.
 **********************************************************************/


constexpr size_t TestConstExpr::factorial(size_t n)
{   
    if(n==0) return 0;

    size_t result = 1;
    while(n > 1)
    {
        if(n > 30) n--;
        else result *= n--;
    }
    return result;
}


/*
constexpr size_t TestConstExpr::factorial(size_t n)
{   
    if(n==0) return 0;
    else if(n==1) return 1;
    else if( n > 30)factorial(n-1);

    return n * factorial(n-1);
}
*/

