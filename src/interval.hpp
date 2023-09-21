#ifndef INTEVAL_H
#define INTEVAL_H

#include <iostream>
#include <limits>
#include <map>

namespace jomt::data
{

template<class K, class V>
class interval
{
    using Key = K;
    using PtrKey = K*;
    using RefKey = K&;

    using Val = V;
    using PtrVal = V*;
    using RefVal = V&;
    

    std::map<Key,Val> m_map;

public:

    //Init the interval with the smalles value.
    interval(): m_map{}
    {
        m_map.emplace(std::make_pair(std::numeric_limits<Key>::min(), std::numeric_limits<Val>::min()));
    }


    auto begin()
    {
        return m_map.begin();
    }

    auto end()
    {
        return m_map.end();
    }


    void insert(Key begin, Key end, Val val)
    {
        auto EQ=[](const Key& a, const Key& b)
        {
             return (!(a < b) && !(b < a));
        };
        
        if(EQ(begin, end)) //Invalid Interval.
            return;

        //Interval[itb, ite)
        auto itb = m_map.end();
        auto ite = m_map.end();

        //-----------------------------------
        //Setting the begin of the interval
        auto it = m_map.lower_bound(begin);
        Val prev = val;

        //C.A the Begin Key is set at the end of the map
        if(it != m_map.begin())
            it--;
        
        itb = it;
        prev = it->second;
        if(prev != val) //insert it and get the iterator
        {
            if(EQ(begin,it->first)) //C.A.1, The previous item has the same Key than the new Key
            {
                it->second = val;
                if(it != m_map.begin()) 
                {
                    it--;
                    if(it->second == val)
                    {
                        auto itd = it;
                        it = m_map.erase(++itd);
                    }
                }
                itb = it;
            }
            else
                itb = m_map.insert(it,{begin, val});
        }

        //-----------------------------------
        //Setting the end of the interval
        it = m_map.lower_bound(end);
        ite = it;
        
        if(it == m_map.end())
        {
            it--;            
            if(itb!=it)
                prev = it->second;
            ite = m_map.insert(it,{end, prev});
        }
        else 
        {
            if(EQ(it->first, end))
                if(prev == it->second)
                    ite++;
                else
                    prev = it->second;
            else
            {
                it--;
                if(it != itb)
                    prev = it->second;
                ite = m_map.insert(it,{end, prev});
            }
            
        }
        
        //-----------------------------------
        //delete the intermediate elements.
        itb++;
        if(itb != ite)
        {
            it = m_map.erase(itb,ite);
            if(it != m_map.end())
            {
                it--;
                if(it != m_map.end() && it->second == ite->second)
                    m_map.erase(ite);
            }
        }
        
    }//insert


}; //class


}//namespace jomt::data

#endif