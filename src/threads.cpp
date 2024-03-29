
#include "threads.h"
#include <thread>
#include <future>
#include <chrono>

using namespace jomt::test;

TAB::TAB() : BaseTA{1}, BaseTB{2} {
    std::cout << "TAB()" << std::endl;
    BaseTA::start();
    BaseTB::start();
}

void TAB::join()
{
    BaseTA::join();
    BaseTB::join();
}

void TAB::on_leap(int id)
{
    std::unique_lock<std::mutex> lck(mtx);
    std::cout << "Message from the thread of Base Class: " << id << "\n";
}

void BaseTA::start()
{
    if (running) return;
    running = true;
    std::cout << "BaseTA::start" << std::endl;
    m_t = std::unique_ptr<std::thread>(new std::thread(&BaseTA::run, this));
}

void BaseTB::start()
{
    if (running) return;
    running = true;
    std::cout << "BaseTB::start" << std::endl;
    m_t = std::unique_ptr<std::thread>(new std::thread(&BaseTB::run, this));
}

void BaseTA::run()
{
    std::cout << "BaseTA::run" << std::endl;
    int counter{0};
    while (running && counter < 10)
    {
        counter++;
        std::this_thread::sleep_for(std::chrono::duration<suseconds_t>(1));
        on_leap(_id);
        
    }
    running = false;
}

void BaseTB::run()
{
    std::cout << "BaseTB::run" << std::endl;
    int counter{0};
    while (running && counter < 10)
    {
        counter++;
        std::this_thread::sleep_for(std::chrono::duration<suseconds_t>(2));
        on_leap(_id);
    }
    running = false;
}
void BaseTA::join() {m_t->join();}
void BaseTB::join() { m_t->join(); }


void CounterClass::increaseSingle()
{
    m_v.lock(); // block access to the variable
    _svalue++;
    m_v.unlock(); // unblock access to the variable
}

void CounterClass::decreaseSingle()
{
    m_v.lock(); // block access to the variable
    _svalue--;
    m_v.unlock(); // unblock access to the variable
}

int CounterClass::readSingle() const
{
    int cpyvl{0};
    m_v.lock(); // block access to the variable
    cpyvl = _svalue; //Get a copy of the value at the moment of reading.
    m_v.unlock(); // unblock access to the variable
    return cpyvl;
}


CounterClass& CounterClass::operator++(int x)
{
    increaseSingle();
    _counter++; //Counter is protected for concurrency by atomic wrapper.
    return *this;
}

CounterClass& CounterClass::operator--(int x)
{   
    decreaseSingle();
    _counter--; //Counter is protected for concurrency by atomic wrapper.
    return *this;
}

/********************************************************************************
 * In this case, the _counter variable is protected for cuncurrency 
 * meanwhile _svalue is accesed trhought its method protected for concurrency.
 * 
 * The class std::unique_lock<std::mutex> will block the concurrency along the
 * execution of the operator (context).
********************************************************************************/
std::ostream& jomt::test::operator<<(std::ostream& out, const CounterClass& o) 
{   
    std::unique_lock<std::mutex> lockop(o.m_out);
    return out << "Counter Trheads is [" << o._counter << "] and  single variable is [" << o.readSingle() << "]";
}


void MyThread::run()
{
    std::cout << "\n(begin)MyThread[" << _name << "] is running.\n";

    for(int cont{1}; cont <= _cycles; cont++)
    {
        if(_type < -1)
            _refObj--;
        else if(_type > 0)
            _refObj++;

        if(cont % 100 == 0)
            std::cout << "\n\tMyThread[" << _name << "] " << _refObj;
    }

    std::cout << "\n(end)MyThread[" << _name << "] has ended.\n";
}

void MyThread::runPromise(std::promise<int> prm)
{
    std::cout << "\n(begin)MyThread[" << _name << "] Running Promise.\n";
    int result;

    for(int cont{1}; cont <= _cycles; cont++)
    {
        
        if(_type < -1)
            result = _refObj--.readSingle();
        else if(_type > 0)
            result = _refObj++.readSingle();

        if(cont % 100 == 0)
            std::cout << "\n\tMyThread[" << _name << "] " << _refObj;
    }

    std::cout << "\nMyThread[" << _name << "] Reading Promise Value\n";
    prm.set_value(result);

std::cout << "\n(end)MyThread[" << _name << "] Losing time.\n";
    for(int i=0; i<1000000; i++)
        int j = i%33;
    std::cout << "\n(end)MyThread[" << _name << "] Returning form promise.\n";
}


void TestThreads::procA()
{
    std::unique_lock<std::mutex> lck(mtx);
    std::cout << "\n[ConditionalVariable] ProcA has started.";

    std::cout << "\n\t[ConditionalVariable] ProcA is waiting for subprocess signal.";
    cv.wait(lck);
    std::cout << "\n[ConditionalVariable] ProcA has been reactivated.";

    std::cout << "\n\t[ConditionalVariable] ProcA Internal Value = " << internalVaule;
    
    std::cout << "\n[ConditionalVariable] ProcA has ended.";
}

void TestThreads::procB()
{
    //std::unique_lock<std::mutex> lcksp(mtx);

    std::cout << "\n[ConditionalVariable] ProcB has started.";

    internalVaule++;
    std::cout << "\n\t[ConditionalVariable] ProcB Internal Value = " << internalVaule;

    std::cout << "\n\t[ConditionalVariable] ProcB will be wating for 2 seconds.";
    std::this_thread::sleep_for(std::chrono::duration<suseconds_t>(2)); 

    internalVaule++;
    std::cout << "\n\t[ConditionalVariable] ProcB Internal Value = " << internalVaule;

    std::cout << "\n\t[ConditionalVariable] ProcB will be wating for 5 seconds.";
    std::this_thread::sleep_for(std::chrono::duration<suseconds_t>(3));

    internalVaule++;
    std::cout << "\n\t[ConditionalVariable] ProcB Internal Value = " << internalVaule;

    std::cout << "\n\t[ConditionalVariable] ProcB **** is notifying to all.****";
    cv.notify_all();
    
    
    std::cout << "\n\t[ConditionalVariable] ProcB will be wating for 2 seconds.";
    std::this_thread::sleep_for(std::chrono::duration<suseconds_t>(3));

    internalVaule++;
    std::cout << "\n\t[ConditionalVariable] ProcB Internal Value = " << internalVaule;

    std::cout << "\n[ConditionalVariable] ProcB has ended.";
}


void TestThreads::test_yield(){
    internalVaule=0;
    std::thread a(&TestThreads::proc_ya, this);
    std::thread b(&TestThreads::proc_yb, this);

    if(a.joinable())
        a.join();
    if(b.joinable())
        b.join();
    std::cout << "\nEnd of Testing Yiedl\n";
}

void TestThreads::my_sleep(std::chrono::milliseconds dur)
{

    auto last = std::chrono::high_resolution_clock::now();
    last += std::chrono::duration_cast<std::chrono::microseconds>(dur);

    while(std::chrono::high_resolution_clock::now() < last)
        std::this_thread::yield();
}

void TestThreads::proc_ya(){
    
    std::cout << "Thread A init\n";
    while(internalVaule < 50)
    {
        std::cout << "Thread A: wait for 500ms" << std::endl;
        my_sleep(std::chrono::milliseconds(500));
        internalVaule++;
        std::cout << " ra[" << internalVaule << "] " << std::endl;
    }
}

void TestThreads::proc_yb(){

    std::cout << "Thread B init\n";
    while(internalVaule < 50)
    {
        internalVaule++;
        std::cout << " rb[" << internalVaule << "] " << std::endl;
        my_sleep(std::chrono::milliseconds(250));
    }
}



void TestThreads::doTest()
{
    std::cout << "\n*** REQUIERES link option: -pthread\n";
    std::cout << "Running test";

    CounterClass counter{};

    
    MyThread mp3("TC--", 7000,-1, counter);
    MyThread mp2("TB++", 2000,1, counter);
    MyThread mp4("TD--", 3000,-1, counter);
    MyThread mp5("TE<<", 5000,0, counter);
    MyThread mp1("TA++", 2000,1, counter);

    std::thread t5(&MyThread::run, &mp5);
    std::thread t1(&MyThread::run, &mp1);
    std::thread t2(&MyThread::run, &mp2);
    std::thread t3(&MyThread::run, &mp3);
    std::thread t4(&MyThread::run, &mp4);
    

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::cout   << "\nThe theads have finished. Final Counter:\n"
                <<  "\t" << counter << "\n"
                <<  "........................\n"
                << "Running with Async:\n"; 

    auto hdl_a = std::async(&MyThread::run, &mp1);
    auto hdl_b = std::async(&MyThread::run, &mp4);

    hdl_a.wait();
    hdl_b.wait();

    std::cout   << "\nThe Asyncs have finished. Final Counter:\n"
                <<  "\t" << counter << "\n"
                <<  "........................\n"
                << "Running with Promise/Futer:\n"; 

    MyThread mpp("TF++", 20000,1, counter);
    std::promise<int> prm1;
    std::future<int> ftr1 = prm1.get_future();

    std::cout << "\nExecutin Promise\n";
    std::thread tp(&MyThread::runPromise, &mpp, std::move(prm1));  

    std::cout << "Fetching Future\n";
    int result = ftr1.get(); //It will wait until the thread finishd and returns the final value.
    
    std::cout << "Future arrives = " << result << "\n";
    
    tp.join();

    std::cout   << "Promise's Thread has ended.\n"
                <<  "........................\n"
                << "Running with Conditional Variable:\n"; 

    std::thread tcv(&TestThreads::procA, this);
    std::thread sbt(&TestThreads::procB, this);
    tcv.join();
    sbt.join();

    std::cout << "\nTesting Inherice Clas." << std::endl;
    TAB tab;
    tab.join();
    std::cout << "Conditional Variable has ended." << std::endl;

    std::cout << "\nTesting Yield." << std::endl;
    test_yield();
    
    
}   