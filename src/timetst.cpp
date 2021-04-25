
#include "timetst.h"

#include<iostream>
#include<iomanip>
#include<ctime>
#include<chrono>
#include<thread>

using namespace jomt::test;
using namespace std::chrono;

std::string TimeTest::strTimeStamp(std::string format, bool bmsec)
{
    std::stringstream out;
    time_t rawtime;
	struct tm * timeinfo;
    char buffer[128];
    
    time(&rawtime);
	timeinfo = localtime(&rawtime);

    //Get the system clock fot NOW
    system_clock::time_point today = system_clock::now(); 

    // Get the time_t from today
    rawtime = system_clock::to_time_t(today); 
    // Convert to time_point fromtd_tm, wich include till seconds.
    system_clock::time_point td_tm = system_clock::from_time_t(rawtime);

    // Get the diferece tiks betwen them.
    system_clock::time_point units(today - td_tm);

    //Getting Milliseconds
    auto mseconds = duration_cast<milliseconds>(units.time_since_epoch()).count(); 

    
    strftime(buffer, 80, format.c_str(), timeinfo);    
    std::string dt2(buffer);
	out << dt2;
    if(bmsec)
	    out << "." << std::setw(3) << std::setfill('0') << mseconds;

    return out.str();
}

void TimeTest::doTest()
{
    std::string format{"%Y-%m-%d %H:%M:%S"};

    std::cout << "Testing without Milliseconds:\n\t"; 
    std::cout << strTimeStamp(format, false) << "\n\nwaiting 10ms\n";
    
    std::cout << "Testing with Milliseconds:\n\t"; 
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << strTimeStamp(format, true) << "\nwaiting 100ms\n\t";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << strTimeStamp(format, true) << "\n";
}
