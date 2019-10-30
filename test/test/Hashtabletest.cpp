#include <gtest/gtest.h>
#include <iostream>
#include <random>
#include <chrono>
#include "hashtable.h"

using namespace std;
using namespace chrono;

TEST(Hashtabletest, get_result)
{
    random_device device;
    default_random_engine engine(device());
    uniform_int_distribution<> dis_key(0, 100000000);
    HashTable * table = new HashTable(5);

    /*ָ��3������,��֤�Ƿ���ȷ*/
    ASSERT_TRUE(table->HashAdd(666, 123));
    ASSERT_TRUE(table->HashAdd(32155, 12345));
    ASSERT_TRUE(table->HashAdd(6668989, 1234567));

    try
    {
        cout << "��ʼ���ݲ���......" << endl;
        for (int i = 0; i < 20000000; ++i)
        {
            table->HashAdd(dis_key(engine), i);
        }
        cout << "���ݲ�����ɣ�" << endl;
    }
    catch (std::bad_alloc&)
    {
        cout << "�ڴ����ʧ��(���ܴ����ڴ治��),������ֹ��" << endl;
        delete table;
        table = NULL;
    }

    auto begin = system_clock::now();
    cout << "��ʼ���ݲ�ѯ......" << endl;
    /*��ѯ2000���*/
    for (int i = 0; i < 20000000; ++i)
    {
        table->HashLookup(i);
    }


    ASSERT_EQ(table->HashLookup(666), 123);
    ASSERT_EQ(table->HashLookup(32155), 12345);
    ASSERT_EQ(table->HashLookup(6668989), 1234567);

    delete table;
    table = NULL;
}