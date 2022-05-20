#ifndef CUSTOM_H
#define CUSTOM_H

#include <string>
#include <iostream>
#include <functional>

namespace jomt::test
{

    class Nil{};

    class KeyClass
    {
        int m_key;

    public:
        KeyClass() = default;

        KeyClass(int key) : m_key{key}
        {
            std::cout << "\n\tC[" << m_key << "](" << this << ") KeyClass.\n";
        }

        ~KeyClass()
        {
            std::cout << "\n\tD[" << m_key << "](" << this << ") ~KeyClass.\n";
        }

        const int &value() { return m_key; }
        void value(int key) { m_key = key; }

        friend bool operator<(const KeyClass &lk, const KeyClass &rk) { return lk.m_key < rk.m_key; }
        friend std::ostream &operator<<(std::ostream &out, const KeyClass &key) { return out << key.m_key; }
    };

    class ValueClass
    {
        std::string m_value;

    public:
        ValueClass() = default;
        ValueClass(std::string value) : m_value{value}
        {
            std::cout << "\n\tC[" << m_value << "](" << this << ") ValueClass.\n";
        }

        ~ValueClass()
        {
            std::cout << "\n\tD[" << m_value << "](" << this << ") ~ValueClass.\n";
        }

        const std::string& value(){return m_value;}

        friend std::ostream &operator<<(std::ostream &out, const ValueClass &val) { return out << val.m_value; }
    };

    class DummyClass
    {
        std::string m_value;
        int i_value;
        bool b_value;


    public:
        DummyClass() = default;
        DummyClass(bool female, std::string name, int age) : m_value{name}, i_value{age}, b_value{female}
        {
            std::cout << "\n\tC[" << m_value << "](" << this << ") DummyClass.\n";
        }

        ~DummyClass()
        {
            std::cout << "\n\tD[" << m_value << "](" << this << ") ~DummyClass.\n";
        }

        const std::string &name() { return m_value; }
        const int &age() { return i_value; }
        const bool &female() { return b_value; }

        friend std::ostream &operator<<(std::ostream &out, const DummyClass &val)
        {
            return out << "name: " << val.m_value << "; age: " << val.i_value << "; female: " << val.b_value;
        }
    };

    class TypeA
    {
        std::string name;

    public :
        TypeA(std::string nm) : name{nm} {}
        friend std::ostream &operator<<(std::ostream &out, const TypeA& obj)
        {
            return out << "TypeA [" << obj.name << "]";
        }
    };

    class TypeB
    {
        std::string name;

    public:
        TypeB(std::string nm):name{nm}{}

        friend std::ostream &operator<<(std::ostream &out, const TypeB &obj)
        {
            return out << "TypeB [" << obj.name << "]";
        }
    };

    struct RestrictedClass
    {
        RestrictedClass() = delete;
        RestrictedClass(RestrictedClass &) = delete;
        ~RestrictedClass() = delete;
    };

    class Dynamic
    {
        KeyClass m_key;
        std::string m_data{};

    public:
        Dynamic() = delete;
        Dynamic(KeyClass &&key):m_key{std::move(key)}{}
        void Key(const int key) { m_key.value(key); }
        const int& Key(){return m_key.value();}
        void data(std::string &&data) { m_data = std::move(data); }
        const std::string& data() { return std::ref(m_data);}

    };

} //namespace

#endif