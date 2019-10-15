#pragma once

#include "singleton.h"
#include <iostream>

namespace utilstest
{
    // ��û�и��Ӽ򵥵ķ���������ȥ�޸�TestSingleton�Ĺ��캯�������Եģ�
    class TestSingleton
    {
    protected:
        TestSingleton() :
            m_ii(0)
        {
            std::cout << "TestSingleton()" << endl;
        }

        TestSingleton(const TestSingleton&)
        {
        }

        TestSingleton& operator=(const TestSingleton&)
        {
        }

    public:
        ~TestSingleton()
        {
        };

        void Fun()
        {
            int i = 0;
            ++i;
        }

    private:
        int m_ii;
    };

    void Test_Singleton()
    {
        std::cout << "Test_Singleton1()" << endl;
        Singleton<TestSingleton>::GetInstance()->Fun();
        std::cout << "Test_Singleton2()" << endl;
        //Singleton<TestSingleton>::s_pInstance;
    }

}
