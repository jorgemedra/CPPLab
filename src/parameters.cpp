
#include "parameters.h"
#include <memory>
#include <iostream>

using namespace jomt::test;

KeyClass&& createKey(int key_i)
{
    std::cout << "\tCreating key by createKey.\n";
    KeyClass key(key_i);

    std::cout << "\treturnning key by return std::move(key);.\n";
    return std::move(key);
    
}

void TestParameters::doTest()
{
    std::cout << "***********************************\n"
              << "TestParameters \n"
              << "***********************************\n\n";

    std::cout << "Testing >> KeyClass&& createKey(int key_i): \n";
    KeyClass key = createKey(33);
    std::cout << "\tThe new key created has the  value:" << key.value() << " which has been moved from createKey().\n\n";

    std::cout << "Testing Constructur with moveable parameter: Dynamic(KeyClass &&key)>\n";

    // Create a new instance of Dynamic class, using the previous key instance got from createKey()
    Dynamic dynamic{std::move(key)};

    std::cout << "\n\tDynamic.Key:" << dynamic.Key() << "\n";
    dynamic.Key(322);
    std::cout << "\n\tNew key value after moved:" << key.value() << "\n";
    std::cout << "\n\tNew dynamic.Key:" << dynamic.Key() << "\n";
    std::cout << "\n\tCheck key value after moved:" << key.value() << "\n";

    std::cout << "Testing >> Moving a Strinn into a Dynamic class: \n";
    std::string data{"This is my data."};

    std::cout << "\n\tOriginal Data 'data': [" << data << "]\n";
    std::cout << "\n\tOriginal Data 'dynamic.data()': [" << dynamic.data() << "]\n";

    dynamic.data(std::move(data));
    std::cout << "\n\tData variable after being moved: [" << data << "]\n";
    std::cout << "\n\tdynamic.data() variable after being moved: [" << dynamic.data() << "]\n";
}