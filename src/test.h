
#ifndef POINTERS_H
#define POINTERS_H

#include <iostream>
#include <sstream>

namespace jomt
{

    enum class TestType: char
    {
        Pointers        = 'p',        //OK
        Consts          = 'c',        //OK
        Mutable         = 'm',        //OK
        Virutal         = 'v',        //OK
        LRValue         = 'r',        //OK
        SmartPointer    = 's',        //OK
        Templates       = 't',        //OK
        ConstExpr       = 'x',        //OK
        Threads         = 'd'         //OK
    };


    class Test
    {
        TestType _type;

    public:

        Test(TestType type): _type{type}{};
        virtual ~Test(){}

        virtual void doTest()=0;
        

        void runTest()
        {
            std::cout   << "-----------------------------\n"
                        << "Running " << info() << "\n";
            doTest();
            std::cout   << "Test Ended"
                        << "-----------------------------\n";             
        }

        std::string info(){
            std::stringstream out;

            out << "Test case: ";

            switch (_type)
            {
            case TestType::Pointers:
                out << " Pointer Test";
                break;
            case TestType::Consts:
                out << " Consts Test";
                break;

            case TestType::Mutable:
                out << " Mutable Test";
                break;

            case TestType::Virutal:
                out << " Virtual Test";
                break;
            
            case TestType::LRValue:
                out << " Left Right Value Test";
                break;

            case TestType::SmartPointer:
                out << " Smart Pointers Test";
                break;

            case TestType::Templates:
                out << " Template Test";
                break;
            
            case TestType::ConstExpr:
                out << " Const Expr Test";
                break;

            case TestType::Threads:
                out << " Threads Test";
                break;

            default:
                out << "UKNOWN Test";
                break;
            }

            out << "\n";
            return out.str();
        }
    };

}
#endif
