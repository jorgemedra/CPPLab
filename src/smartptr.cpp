
#include "smartptr.h"
#include <iostream>
#include <memory>


using namespace jomt::test;


void MemDummy::printInfo()
{
    std::cout << "[" << _name << "] MemDummy Address: " << this << "\n\n";
}

void TestSmartPtr::doTest()
{   
    std::cout   << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
                <<"Testing unique_ptr\n\n";
    testUniqPrt();
    std::cout   << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";

    std::cout   << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
                <<"Testing shared_ptr\n\n";
    testSharedPrt();
    std::cout   << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";

    std::cout   << "\n<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
                <<"Testing testWeakPrt\n\n";
    testWeakPrt();
    std::cout   << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    
}

void TestSmartPtr::testUniqPrt()
{
    std::cout << "\nTesting Unique Ptr: Init Main Context ot Test\n\n";
    std::unique_ptr<MemDummy> upM{new MemDummy("T1_Ptr_Main")};
    upM->printInfo();
    
    std::cout << "Testing Unique Ptr: Init to Context 1\n";
    {   
        std::unique_ptr<MemDummy> up1{new MemDummy("T1_Ptr1")};
        up1->printInfo();
    }
    std::cout << "Context 1 Ended\n\n";

    std::cout << "Testing Unique Ptr: Init to Context 2\n";
    {   
        std::unique_ptr<MemDummy> up2{new MemDummy("T1_Ptr2")};
        up2->printInfo();
    }
    std::cout << "Context 2 Ended\n\n";

    upM->printInfo();
    std::cout << "Testing Unique Ptr: Finishing Main Context ot Test\n";
}

void TestSmartPtr::testSharedPrt()
{
    std::cout << "\nTesting Shared Ptr: Init Main Context ot Test\n\n";
    std::shared_ptr<MemDummy> spM{new MemDummy("T1_PtrShr_Main")};
    
    spM->printInfo();
    std::cout << "\nMain Share Pointer Counter: " << spM.use_count() << "\n";

    std::cout << "Testing Shared Ptr: Init to Context 1\n";
    {   
        std::shared_ptr<MemDummy> sp2 = spM;
        sp2->printInfo();
        std::cout << "\nMain Share Pointer Counter: " << spM.use_count() << "\n";
    }
    std::cout << "Context 1 Ended\n\n";

    std::cout << "\nMain Share Pointer Counter: " << spM.use_count() << "\n";

    std::cout << "Testing Shared Ptr: Init to Context 2\n";
    {   
        std::shared_ptr<MemDummy> sp3 = spM;
        sp3->printInfo();
        std::cout << "\nMain Share Pointer Counter: " << spM.use_count() << "\n";
    }

    std::cout << "Context 2 Ended\n\n";

    std::cout << "\nMain Share Pointer Counter: " << spM.use_count() << "\n";

    std::cout << "Testing Shared Ptr: Finishing Main Context ot Test\n";
}



/*
    Weak Pointer will be alive until the share point, or Owner has ended.

    IT MUST be created from another Weak Pointer or Shared Pointer.
*/
void TestSmartPtr::testWeakPrt()
{

    std::cout << "\nTesting Weak Ptr: Init Main Context ot Test\n\n";

    {   //Weak Context
        std::weak_ptr<MemDummy> wp;
        
        std::cout << "Weak Ptr before assinged shareptr: " << wp.use_count() << " Expired: " << wp.expired() << "\n";
        { //shared pointer
            std::shared_ptr<MemDummy> sp = std::make_shared<MemDummy>("Shared Owner");
            std::cout << "\tShared Ptr: " << sp.use_count() << "\n"
                      << "wp = sp;\n"
                      << "std::weak_ptr<MemDummy> wp3(sp);\n";
            
            wp = sp;
            
            { //Context of Wp3
                std::weak_ptr<MemDummy> wp3(sp);

                std::cout << "\tShared Ptr: " << sp.use_count() << "\n";
                std::cout << "\tWeak Ptr before assing shareptr: " << wp.use_count() << " Expired: " << wp.expired() << "\n";
                std::cout << "\tWeak Ptr3 before assing shareptr: " << wp3.use_count() << " Expired: " << wp3.expired() << "\n";
            }

            sp->printInfo();
            if(!wp.expired())
                wp.lock()->printInfo();
            
            std::cout << "leaving Shared Ptr context.\n";
        }
        std::cout << "Weak Ptr After assinged leaving SharePtr Context: " << wp.use_count() << " Expired: " << wp.expired() << "\n";
        
        if(!wp.expired())
            wp.lock()->printInfo();
        else
            std::cout << "Weak Ptr has exipired.\n";
    }

    std::cout << "\nTesting Weak Ptr: Finished\n\n";

}