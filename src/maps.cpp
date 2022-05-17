
#include <cstdio>
#include <map>
#include "maps.h"
#include "custom.h"

using namespace jomt::test;

/**
 * @brief this test shows how maps create some instances of Key and Values Classes to
 * be used into the pair and maps. In the end, the original instance is not stored into
 * the map but a copy is did so.
 * 
 * To prove it, a message into each constructor and destructor is showe each time 
 * that an instance is created.
 */
void MapTest::test1()
{
    std::cout << "\nMap Test, passing elements by copy: \n";

    std::map<KeyClass, ValueClass> m_map;

    {
        std::cout << "\n1. Creating Keys and Values\n";
        KeyClass k1{10};        
        KeyClass k2{20};
        ValueClass v1{"value 1"};
        ValueClass v2{"value 2"};

        std::cout << "\n2. Inserting elements KVP by copy.\n";
        m_map.insert(std::pair<KeyClass, ValueClass>(k1,v1));
        m_map.insert(std::pair<KeyClass, ValueClass>(k2, v2));

        std::cout << "\n3. Leaving Context.\n";
    }

    std::cout << "\n4. Listing all elements in map.\n";
    std::cout << std::endl;
    for (auto it = m_map.begin(); it != m_map.end(); it++)
        std::cout << " [" << it->first << ":" << it->second << "]";
        
    std::cout << std::endl;
    std::cout << "\n5. Finish Test1.\n";
}

/**
 * @brief Like test 1, using rvalues, the compiler creates copy of Keys and Values.
 */
void MapTest::test2()
{
    std::cout << "\n\nMap Test, passing elements by rvalue: \n";

    std::map<KeyClass, ValueClass> m_map;

    {
        std::cout << "\n1. Inserting elements KVP by rvalue.\n";
        m_map.insert({{15}, {"value 1"}});
        m_map.insert({{25}, {"value 2"}});
        std::cout << "\n2. Leaving Context.\n";
    }

    std::cout << "\n3. Listing all elements in map.\n";
    std::cout << std::endl;
    for (auto it = m_map.begin(); it != m_map.end(); it++)
        std::cout << " [" << it->first << ":" << it->second << "]";

    std::cout << std::endl;
    std::cout << "\n5. Finish Test1.\n";
}

void MapTest::test3()
{
    std::cout << "\n\nMap Test, passing elements by forwarding: \n";

    std::map<KeyClass, ValueClass> m_map;

    {
        std::cout << "\n1. Inserting elements KVP by forwarding.\n";
        auto p1 = std::pair<KeyClass, ValueClass>(std::forward<KeyClass>(KeyClass(15)), std::forward<ValueClass>(ValueClass("value 1")));
        auto p2 = std::pair<KeyClass, ValueClass>(std::forward<KeyClass>(KeyClass(25)), std::forward<ValueClass>(ValueClass("value 2")));
        m_map.insert(std::forward<std::pair<KeyClass, ValueClass>>(p1));
        m_map.insert(std::forward<std::pair<KeyClass, ValueClass>>(p2));
        std::cout << "\n2. Leaving Context.\n";
    }

    std::cout << "\n3. Listing all elements in map.\n";
    std::cout << std::endl;
    for (auto it = m_map.begin(); it != m_map.end(); it++)
        std::cout << " [" << it->first << ":" << it->second << "]";

    std::cout << std::endl;
    std::cout << "\n4. Finish Test1.\n";
}

/**
 * @brief This way is the best to optimize the memory because the Class are
 * 
 *  1. created into the map, which means that there is onlo one instance of the Class
 *  2. Destroyed according the life time of the map, or any remove operation.
 * 
 */
void MapTest::test4()
{
    std::cout << "\n\nMap Test, passing elements by Emplace: \n";

    std::map<KeyClass, ValueClass> m_map;

    {
        std::cout << "\n1. Inserting elements KVP by forwarding.\n";
        m_map.emplace(21, "data 21");
        m_map.emplace(22, "data 22");
        std::cout << "\n2. Leaving Context.\n";
    }

    std::cout << "\n3. Listing all elements in map.\n";
    std::cout << std::endl;
    for (auto it = m_map.begin(); it != m_map.end(); it++)
        std::cout << " [" << it->first << ":" << it->second << "]";

    std::cout << "\n\n4. Deleting one item.\n";

    auto it = m_map.find(22);
    m_map.erase(it);
    std::cout << std::endl;

    std::cout << "\n5. Finish Test1.\n";
}

void MapTest::doTest()
{
    test1();
    test2();
    test3();
    test4();
}