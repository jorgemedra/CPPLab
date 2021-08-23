
/************************************************************
 * 
 * The main characteristic of StringView is that string_view 
 * takes a reference from the string where it's been created
 * instead od copy it, so if we check this code:
 * 
 *  void myFunc(const std::string data){...} 
 *  
 *  myFunc("My Const String")  //By Copy
 * 
 * It will create a copy of the "My Const String" into the 
 * function myFunc, due to the class std::string operates in
 * this way (Copyable and Contructable).
 * 
 * But,if we use std::string_view instead of std::string
 * the function myFunc will recive a reference, through the 
 * strinv_view, skiping the operation to copy the string which 
 * was used to invoke the funtion, like if it was invoked by
 * referece.
 * 
 * void myFunc(const std::string_view data){...} 
 * 
 *  myFunc("My Const String")  //By Reference
 * 
 * So, the main differente between string and string_view is the
 * performance because the copiable operation is skiped and it 
 * is replaced by a reference operation, so:
 * 
 * 
 * const char* str = "MY String";
 * size_t n = len(str);
 * 
 *  // Copy constructor, wich implies O(n), due the copy of the 
 *  // whole string operation.
 * void myFunc(const std::string data){...} 
 * 
 *  // Reference constructor, wich implies O(1), due the copy of 
 *  // the reference of the string.
 * void myFunc(const std::string_view data){...} 
 ************************************************************/ 


#include "str_view.h"
#include <string_view>
#include <string>


using namespace jomt::test;


void testSring(std::string data){    
    std::cout << "\n\tAdress of data = " << (void*)&data[0];
    std::cout << "\n\tIt will be different from the source";
}

void testSringView(std::string_view  data){    
    std::cout << "\n\tAdress of data = [" << (void*)&data[0] << "]";
    std::cout << "\n\tIt will be EQUAL from the source";
}

void TestStringView::doTest()
{
    const char* data{"This is my data."};
    

    std::cout << "Original String: [" << data << "], Address = [" << (void*)data << "]";
    
    std::cout << "\n\nUsing 'testSring(std::string_view  data)\n";
    testSring(data);

    std::cout << "\n\nUsing 'testSringView(std::string_view  data)\n";
    testSringView(data);
    std::cout << "\n\n";
}