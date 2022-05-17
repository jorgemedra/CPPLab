#ifndef METSPROG_H
#define METSPROG_H

#include "test.h"


namespace jomt::test
{

    class MetaTest : public Test
    {
        
        void TestTypeFunc();    
        void TestValidProperties();
        void TestConditionals();

        void TestIteratorAndRec();

        void TestVariadic(); //PENDING

    public:
        
        MetaTest() : Test(jomt::TestType::Meta){}
        void doTest();
    };


} // namespace jomt::test

#endif