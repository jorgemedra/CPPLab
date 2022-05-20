
#include <cstdio>
#include <iostream>
#include <array>

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
#include "maps.h"
#include "tpair.h"
#include "metaprog.h"
#include "parameters.h"
#include "test_matrix.h"

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
    const static std::string MAPS;
    const static std::string PAIRS;
    const static std::string META;
    const static std::string PARAMS;
    const static std::string MATRIX;
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
const std::string M_CMDS::MAPS{"maps"};
const std::string M_CMDS::PAIRS{"pairs"};
const std::string M_CMDS::META{"metap"};
const std::string M_CMDS::PARAMS{"params"};
const std::string M_CMDS::MATRIX{"matrix"};

std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    auto pipe = popen(cmd, "r"); // get rid of shared_ptr

    if (pipe == 0)
        throw std::runtime_error("popen() failed!");

    std::cout << "POPE READING" << std::endl;
    while (!feof(pipe))
    {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }

    std::cout << "RESULT: " << std::endl
              << result << std::endl;
              
    auto rc = pclose(pipe);

    if (rc == EXIT_SUCCESS)
    { // == 0
    }
    else if (rc == EXIT_FAILURE)
    { // EXIT_FAILURE is not used by all programs, maybe needs some adaptation.
    }
    return result;
}

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
        else if(opt.compare(M_CMDS::MAPS)  == 0)
        {
            MapTest tsm;
            tsm.runTest();
        }
        else if(opt.compare(M_CMDS::PAIRS)  == 0)
        {
            TestPair tpr;
            tpr.runTest();
        }
        else if (opt.compare(M_CMDS::META) == 0)
        {
            MetaTest mttp;
            mttp.runTest();
        }
        else if (opt.compare(M_CMDS::PARAMS) == 0)
        {
            jomt::test::TestParameters prmtst;
            prmtst.runTest();
        }

        else if (opt.compare(M_CMDS::MATRIX) == 0)
        {
            jomt::test::TestMatrix mtrx;
            mtrx.runTest();
        }
    }
    while(opt.compare(M_CMDS::QT) != 0);

    return 0;
}

void printHelp()
{
    std::cout << "\n-----------------------\n"
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
              << "\t" << M_CMDS::MAPS << ": Maps Test.\n"
              << "\t" << M_CMDS::PAIRS << ": Pairs & Tuples Test.\n"
              << "\t" << M_CMDS::META << ": Metaprograming Test.\n"
              << "\t" << M_CMDS::PARAMS << ": Parameters Test.\n"
              << "\t" << M_CMDS::MATRIX<< ": Matrix Operations.\n"
              << "-----------------------\n\n"
              << "$ ";
}