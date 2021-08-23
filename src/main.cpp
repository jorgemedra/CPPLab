
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
#include "timetst.h"
#include "file.h"
#include "lambdas.h"
#include "str_view.h"

using namespace jomt::test;

void printHelp();

struct M_CMDS
{
    const static std::string QT;
    const static std::string PTRS;
    const static std::string CONST;
    const static std::string MUTBL;
    const static std::string VRTL;
    const static std::string LRVL;
    const static std::string SMRPTR;
    const static std::string TMPLTS;
    const static std::string CNSTXPR;
    const static std::string THRD;
    const static std::string TM;
    const static std::string FL;
    const static std::string LMBDS;
    const static std::string STRVW;
};

const std::string M_CMDS::QT{"quit"};
const std::string M_CMDS::PTRS{"ptrs"};
const std::string M_CMDS::CONST{"const"};
const std::string M_CMDS::MUTBL{"mutable"};
const std::string M_CMDS::VRTL{"virtual"};
const std::string M_CMDS::LRVL{"lrvalue"};
const std::string M_CMDS::SMRPTR{"smartptr"};
const std::string M_CMDS::TMPLTS{"templates"};
const std::string M_CMDS::CNSTXPR{"constexpr"};
const std::string M_CMDS::THRD{"threads"};
const std::string M_CMDS::TM{"time"};
const std::string M_CMDS::FL{"file"};
const std::string M_CMDS::LMBDS{"lambdas"};
const std::string M_CMDS::STRVW{"strview"};

int main()
{
    std::string opt{""};

    do{
        printHelp();
        std::cin >> opt;
        
        for(size_t idx = 0; idx < opt.size(); idx++)
            opt[idx] = std::tolower(opt[idx]);

        if( opt.compare(M_CMDS::PTRS)  == 0) 
        {
                TestPointer tPointer;
                tPointer.runTest();
        }
        else if(opt.compare(M_CMDS::CONST)  == 0)
        {
            TestConst tConst;
            tConst.runTest();
        }
        else if(opt.compare(M_CMDS::MUTBL)  == 0)
        {
            TestMutable tMut;
            tMut.runTest();
        }
        else if(opt.compare(M_CMDS::VRTL)  == 0)
        {
            TestVirtual tVir;
            tVir.runTest();
        }
        else if(opt.compare(M_CMDS::LRVL)  == 0)
        {
            TestRLValue tRL;
            tRL.runTest();
        }
        else if(opt.compare(M_CMDS::SMRPTR)  == 0)
        {
            TestSmartPtr tSP;
            tSP.runTest();
        }
        else if(opt.compare(M_CMDS::TMPLTS)  == 0)
        {
            TestTemplate tTmpt;
            tTmpt.runTest();
        }
        else if(opt.compare(M_CMDS::CNSTXPR)  == 0)
        {
            TestConstExpr tCE;
            tCE.runTest();
        }
        else if(opt.compare(M_CMDS::THRD)  == 0)
        {
            TestThreads tt;
            tt.runTest();
        }
        else if(opt.compare(M_CMDS::TM)  == 0)
        {
            TimeTest ttm;
            ttm.runTest();
        }
        else if(opt.compare(M_CMDS::FL)  == 0)
        {
            FileTest ft;
            ft.runTest();
        }
        else if(opt.compare(M_CMDS::LMBDS)  == 0)
        {
            LambdaTest lbt;
            lbt.runTest();
        }
        else if(opt.compare(M_CMDS::STRVW)  == 0)
        {
            TestStringView tsv;
            tsv.runTest();
        }
    }
    while(opt.compare(M_CMDS::QT) != 0);

    return 0;
}


void printHelp()
{
    std::cout   << "\n-----------------------\n"
                << "Commands:\n"
                << "\t" << M_CMDS::QT << ": Quit.\n"
                << "\t" << M_CMDS::PTRS << ": Pointers Test.\n"
                << "\t" << M_CMDS::CONST << ": Consts Test.\n"
                << "\t" << M_CMDS::MUTBL << ": Mutable Test.\n"
                << "\t" << M_CMDS::VRTL << ": Virutal Test.\n"
                << "\t" << M_CMDS::LRVL << ": LRValue Test.\n"
                << "\t" << M_CMDS::SMRPTR << ": Smart Pointers Test.\n"
                << "\t" << M_CMDS::TMPLTS << ": Templates Test.\n"
                << "\t" << M_CMDS::THRD << ": Threads Test.\n"
                << "\t" << M_CMDS::CNSTXPR << ": Constant Expr Test.\n"
                << "\t" << M_CMDS::TM << ": Time Test.\n"
                << "\t" << M_CMDS::FL << ": File Test.\n"
                << "\t" << M_CMDS::LMBDS << ": Lambdas Test.\n"
                << "\t" << M_CMDS::STRVW << ": String View Test.\n"
                << "-----------------------\n\n"
                << "::$";
}