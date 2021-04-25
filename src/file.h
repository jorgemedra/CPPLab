

/******************************************************
READ documentation to know about how to set flags on
compilation and link commands

https://en.cppreference.com/w/cpp/filesystem
*******************************************************/

#ifndef FILET_H
#define FILET_H

#include "test.h"
//#include <iostream>

namespace jomt::test
{

    class FileTest: public jomt::Test
    {
        //void sizeOfFile(std::string file);


    public:
        FileTest(): jomt::Test(jomt::TestType::File){}
        ~FileTest(){}

        void doTest();
    };

}

#endif