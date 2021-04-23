
#include <cstdio>
#include <iostream>

#include "pointer.h"
#include "const.h"
#include "mutable.h"
#include "virtual.h"
#include "rlvalue.h"
#include "smartptr.h"
#include "template.h"
#include "constex.h"
#include "threads.h"

using namespace jomt::test;

void printHelp();

int main()
{
    char opt{0};

    do{
        printHelp();
        std::cin >> opt;

        if( opt == (int)jomt::TestType::Pointers ) 
        {
                TestPointer tPointer;
                tPointer.runTest();
        }
        else if( opt == (int)jomt::TestType::Consts ) 
        {
            TestConst tConst;
            tConst.runTest();
        }
        else if( opt == (int)jomt::TestType::Mutable ) 
        {
            TestMutable tMut;
            tMut.runTest();
        }
        else if( opt == (int)jomt::TestType::Virutal ) 
        {
            TestVirtual tVir;
            tVir.runTest();
        }
        else if( opt == (int)jomt::TestType::LRValue ) 
        {
            TestRLValue tRL;
            tRL.runTest();
        }
        else if( opt == (int)jomt::TestType::SmartPointer ) 
        {
            TestSmartPtr tSP;
            tSP.runTest();
        }
        else if( opt == (int)jomt::TestType::Templates ) 
        {
            TestTemplate tTmpt;
            tTmpt.runTest();
        }
        else if( opt == (int)jomt::TestType::ConstExpr ) 
        {
            TestConstExpr tCE;
            tCE.runTest();
        }
        else if( opt == (int)jomt::TestType::Threads ) 
        {
            TestThreads tt;
            tt.runTest();
        }
    }
    while(opt != 'q');

    return 0;
}


void printHelp()
{
    std::cout   << "\n-----------------------\n"
                << "Test Menu:\n"
                << "\tq: Quit.\n"
                << "\tp: Pointers Test.\n"
                << "\tc: Consts Test.\n"
                << "\tm: Mutable Test.\n"
                << "\tv: Virutal Test.\n"
                << "\tr: LRValue Test.\n"
                << "\ts: Smart Pointers Test.\n"
                << "\tt: Templates Test.\n"
                << "\td: Threads Test.\n"
                << "\tx: Constant Expr Test.\n"
                << "-----------------------\n\n";
}