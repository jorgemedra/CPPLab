
#include "test_matrix.h"
#include "matrix.hpp"
#include <iostream>

using namespace jomt::test;
using namespace  jomt::data;

void TestMatrix::doTest()
{
    std::cout << "Testing Matrix Template:\n";

    test_1();
    test_2();
    test_3();
    test_4();

    std::cout << std::endl;
}

void TestMatrix::test_1()
{
    std::cout << "***************************\n"
              << "Testing Matrix\n"
              << "\tAdding/Subsctractic operations\n"
              << "***************************\n";

    matrix<int, 3, 3> mtrx_a({ {1, 2, 3},
                                {4, 5, 6},
                                {7, 8, 9} });

    std::cout << "MA\n" << mtrx_a.info() << "\n";

    mtrx_a += mtrx_a;
    std::cout << "MA += MA \n"
              << mtrx_a.info() << "\n";
    

    matrix<int, 3, 3> mtrx_b = mtrx_a + mtrx_a;
    std::cout << "MB = MA + MA \n"
              << mtrx_b.info() << "\n";

    std::cout << "MA, must be equal after last operation\n"
              << mtrx_a.info() << "\n";
}

void TestMatrix::test_2()
{
    std::cout << "***************************\n"
              << "Testing Matrix\n"
              << "\tMult by an Scalar.\n"
              << "***************************\n";

    matrix<float, 2, 4> mtrx_a({{1, 2, 3, 4},
                              {4, 5, 6, 7}});
    float scalar = 3.141516;

    std::cout << "MA\n"
              << mtrx_a.info() << "\n";

    mtrx_a *= scalar;

    std::cout << "MA * " << scalar << "\n"
              << mtrx_a.info() << "\n";
}

void TestMatrix::test_3()
{
    std::cout << "***************************\n"
              << "Testing Matrix\n"
              << "\tMult by another Matrix.\n"
              << "***************************\n";

    matrix<long, 3, 3> mtrx_a({{1, 2, 3},
                                {2, 3, 4,},
                                {3, -4, -5}});

    matrix<long, 3, 3> mtrx_b({{0, 1, 2},
                               {-1, 2, 3},
                               {4, 2, 1}});

    std::cout << "MA\n"
              << mtrx_a.info() << "\n";

    std::cout << "MB\n"
              << mtrx_b.info() << "\n";

    std::cout << "MA * MB\n"
              << (mtrx_a * mtrx_b).info() << "\n";

    std::cout << "MB * MA\n"
              << (mtrx_b * mtrx_a).info() << "\n";
}

void TestMatrix::test_4()
{
    std::cout << "***************************\n"
              << "Testing Matrix\n"
              << "\tMult Vectors.\n"
              << "***************************\n";

    matrix<long, 1, 3> mtrx_a({{1, 5, 7}});

    matrix<long, 3, 1> mtrx_b({{0},
                               {-2},
                               {3}});

    std::cout << "MA\n"
              << mtrx_a.info() << "\n";

    std::cout << "MB\n"
              << mtrx_b.info() << "\n";

    std::cout << "MA * MB\n"
              << (mtrx_a * mtrx_b).info() << "\n";

    std::cout << "MB * MA\n"
              << (mtrx_b * mtrx_a).info() << "\n";
}