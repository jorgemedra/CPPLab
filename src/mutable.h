
#ifndef MUTALBE_H
#define MUTALBE_H

#include "test.h"

namespace jomt::test
{
    class TestMutable: public jomt::Test
    {
        int _intValue;
        mutable int _mutInt;
        void printInfo(std::string info) const;
    public:

        void modMut() const;
        void notConst();

        TestMutable():Test(jomt::TestType::Mutable),_intValue{0},_mutInt{0}{}
        void doTest();
    };
}

#endif
