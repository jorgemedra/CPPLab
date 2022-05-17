
#ifndef TRHEADS_H
#define TRHEADS_H

#include "test.h"
#include <iostream>
#include <atomic>
#include <mutex>
#include <thread>
#include <future>
namespace jomt::test
{

    /********
     * This class use a Mutext value to protect the _svalue variable for concurrency
     */ 
    class CounterClass
    {

        // Object to Sinchronize the access to specific element.
        // it is mutable to be access throught the conts methods like 'readSingle'
        mutable std::mutex m_v;
        mutable std::mutex m_out; 

        std::atomic<int> _counter; //Variable protected for concurrecy
        int _svalue;    // Variable not protected for for concurrecy

        void increaseSingle();
        void decreaseSingle();

    public:
        CounterClass():_counter{0}{}

        int readSingle() const;

        void linkPromise();
        CounterClass& operator++(int);
        CounterClass& operator--(int);
        friend std::ostream& operator<<(std::ostream&, const CounterClass&);
    };



    class MyThread
    {
        std::string _name;
        int _cycles;
        int _type;  // -1:--; 0:<<; 1:++
        CounterClass& _refObj;

    public:
        MyThread(std::string name, int cycles, int type, CounterClass& counter):
            _name{name}, _cycles{cycles}, _type{type}, _refObj{counter}{}
        void run();
        void runPromise(std::promise<int>);
    };

    class BaseTA
    {
        int _id;
        bool running;
        std::unique_ptr<std::thread> m_t;

    public:
        BaseTA(int id) : _id{id}, running{false} {}
        ~BaseTA(){}
        void start();
        void join();
        void run();
        
        virtual void on_leap(int id) = 0;
    };

    class BaseTB
    {
        int _id;
        bool running;
        std::unique_ptr<std::thread> m_t;

    public:
        BaseTB(int id) : _id{id}, running{false} {}
        ~BaseTB() {}
        void start();
        void join();
        void run();

        virtual void on_leap(int id) = 0;
    };

    class TAB : public BaseTA, public BaseTB
    {
        std::mutex mtx;
        public:
            TAB();
            void join();
            void on_leap(int id);
    };

    class TestThreads:public jomt::Test
    {
        int internalVaule;
        std::mutex mtx;
        std::condition_variable cv;

    public:

        TestThreads():jomt::Test(jomt::TestType::Threads), internalVaule{0}{}
        ~TestThreads(){}
        
        void doTest();

        void procA();
        void procB();

    };


    /******************************************************************
     * util functions for this test
    ******************************************************************/
    std::ostream& operator<<(std::ostream&, const CounterClass&);
} 

#endif