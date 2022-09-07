
#include <cstdio>
#include <map>
#include "maps.h"
#include "custom.h"
#include "interval.hpp"

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

/**
 * @brief Advance thechnics for search and isert into an order map.
 * 
 */
void MapTest::test5()
{

    std::cout << "\n\nTest5: Advanced thechnics: \n";
    std::map<int,int> m;

    //Amortizing each insertion element
    auto iti = m.begin(); 
    for(int i=1; i<100;i+=2)
        iti = m.insert(iti, {i,i});


    std::cout << "\na):Inserting thr Key 50 and retriving the pointer, to go throught it.\n";

    auto it = m.insert(m.begin(), {50,150}); //O(long(m.size()))
    std::cout << "\n\ta]: IT   [K:V] = [" << it->first << ":" << it->second << "]\n";
    it--;
    std::cout << "\n\ta]: --IT [K:V] = [" << it->first << ":" << it->second << "]\n";
    it++;
    std::cout << "\n\ta]: ++IT [K:V] = [" << it->first << ":" << it->second << "]\n";
    it++;
    std::cout << "\n\ta]: ++IT [K:V] = [" << it->first << ":" << it->second << "]\n";


    std::cout << "\nb):Look for the first element that is not less than 60.\n";

    it = m.lower_bound(60); //O(long(m.size()))
    std::cout << "\n\tb]: IT   [K:V] = [" << it->first << ":" << it->second << "]\n";
    std::cout << "\n\tb]: Inserting {60,160} from IT will amortize the operation\n";
    m.insert(it,{60,160});


    std::cout << "\nc):Look for the first element that is greater than 62.\n";

    it = m.upper_bound(62); //O(long(m.size()))
    std::cout << "\n\tc]: IT   [K:V] = [" << it->first << ":" << it->second << "]\n";
    std::cout << "\n\tc]: Inserting {62,162} from IT will amortize the operation\n";
    m.insert(it,{62,162});


    std::cout << "\nd):Remove the Interval [51,69), open interval.\n";

    auto itf = m.find(51);
    auto itl = m.find(69);
    m.erase(itf,itl);

    std::cout << "\n\tc]: IT LAST   [K:V] = [" << itl->first << ":" << itl->second << "]\n";
}


/**
 * @brief testig the Interval Data Stucture which has been made over a map structure.
 */
void MapTest::test6()
{
    std::cout << "\n\nTest6: testing the Interval Data Structure: \n";

    jomt::data::interval<unsigned int, unsigned short> m_int;

    auto showInt = [](jomt::data::interval<unsigned int, unsigned short>& m_i)
    {
        std::cout << "{";
        for(auto it = m_i.begin(); it != m_i.end(); it++)
            std::cout << " [" << it->first << ":" << it->second << "] ";
        std::cout << "}" << std::endl;
    };


    std::cout << "a. The initial status of interval<int, short>\n\t";
    showInt(m_int);

    m_int.insert(0, 10, 1);
    std::cout << "\nCase A inserting[0,10):1}\n\t";
    showInt(m_int);

    m_int.insert(5, 10, 1);
    std::cout << "\nCase B inserting[5,10):1}\n\t";
    showInt(m_int);

    m_int.insert(5, 8, 4);
    std::cout << "\nCase C inserting[5,8):4}\n\t";
    showInt(m_int);


    m_int.insert(5, 8, 1);
    std::cout << "\nCase D inserting[5,8):1}\n\t";
    showInt(m_int);

    m_int.insert(5, 15, 2);
    std::cout << "\nCase E inserting[5,15):2}\n\t";
    showInt(m_int);

    m_int.insert(8, 10, 3);
    std::cout << "\nCase F inserting[8,10):3}\n\t";
    showInt(m_int);

    m_int.insert(7, 11, 4);
    std::cout << "\nCase G inserting[7,11):4}\n\t";
    showInt(m_int);

    m_int.insert(0, 15, 0);
    std::cout << "\nCase H inserting[0,15):0}\n\t";
    showInt(m_int);

    return;
}

void MapTest::doTest()
{
    // test1();
    // test2();
    // test3();
    // test4();
    //test5();
    test6();
}