
#ifndef TIMETST_H
#define TIMETST_H

#include "test.h"
#include <iostream>

namespace jomt::test
{

    class TimeTest: public jomt::Test
    {
        std::string strTimeStamp(std::string format, bool msec);

    public:
            TimeTest():jomt::Test(jomt::TestType::Time){}
            ~TimeTest(){};

            void doTest();
    };
}
#endif