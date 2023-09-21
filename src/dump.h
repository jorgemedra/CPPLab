#ifndef DUMPL_H
#define DUMPL_H

#include "test.h"


/**
 * @brief Use, on a commmond console of linux:
 *  a) coredumpctl list    To identify the core file
 *  b) coredumpctl [PID|EXE...]    To open del dumpfile to debug with gdb
 * 
 * onece the GDB is running, use the commando bt, or bt full to print the 
 * stack and check the point where the program raise the error.
 * 
 */

namespace jomt::test
{
    class TestDump: public jomt::Test
    {
        void raise_an_exception();
    public:

        TestDump():Test(jomt::TestType::Dump){}
        void doTest();
    };
}

#endif