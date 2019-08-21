#include <iostream>
#include <random>
#include <chrono>
using namespace std;
using namespace chrono;
struct Node
{
    unsigned int key = NULL;
    int value = NULL;
    Node * next = NULL;

    Node() : next(NULL){}
    Node(unsigned key, int value, Node * next) :
        key(key), value(value), next(next) {}
   ~Node(){}
};

class HashTable
{
private:
    Node ** nodes;       /*节点数组*/
    int count;          /*哈希表中元素的实际数量*/
    int table_size;     /*哈希表容量长度*/
    int threshold;      /*阈值,阈值 = 哈希表容量长度 * 加载因子(这里默认设为0.75)*/

public:
    HashTable(int table_size) : count(0), table_size(table_size)
    {
        nodes = new Node*[table_size]();
        threshold = table_size * 0.75;
    }

    ~HashTable()
    {
        int sum = 0;
        for (auto i = 0; i < table_size; ++i)
        {
            for (Node * it = nodes[i]; it != NULL; )
            {
                Node * tmp = it->next;
                delete it;
                sum++;
                it = tmp;
            }
        }
        delete[] nodes;
        nodes = NULL;
    }

    inline int Hash(int key)
    {
        return key % table_size;
    }

    /*插入节点,无法插入key已经存在的值*/
    bool HashAdd(unsigned int key, int value)
    {
        if (count >= threshold)
        {
            rehash();
        }
        if (-1 == HashLookup(key))
        {
            int index = Hash(key);
            nodes[index] = new Node(key, value, nodes[index]);
            count++;
            return true;
        }
        else
        {
            return false;
        }    
    }

    /*删除节点*/
    int HashDel(unsigned int key)
    {
        int index = Hash(key);
        auto it = nodes[index];
        auto pre = nodes[index];
        for (; it != NULL; it = it->next)
        {
            if (it->key == key)
            {
                unsigned int old_value = it->value;
                pre->next = it->next;
                count--;
                delete it;
                return old_value;
            }
            pre = it;
        }
        return 0;
    }
    /*查询节点*/
    int HashLookup(unsigned int key)
    {
        int index = Hash(key);
        for (auto it = nodes[index]; it != nullptr; it = it->next)
        {
            if (it->key == key)
            {
                return it->value;
            }
        }
        return -1;
    }

    /*扩容,并重新hash*/
    void rehash()
    {
        int old_size = table_size;
        Node ** old_array = nodes;

        int new_size = 2 * old_size;
        nodes = new Node*[new_size]();
        table_size = new_size;
        threshold = new_size * 0.75;

        for (int i = 0; i < old_size; ++i)
        {
            for (auto it = old_array[i]; it != NULL; )
            {
                auto e = it;
                it = it->next;
                int index = Hash(e->key);
                e->next = nodes[index];
                nodes[index] = e;
            }
        }
        delete[] old_array;
        old_array = NULL;
    }
};

int main()
{
    random_device device;
    default_random_engine engine(device());
    uniform_int_distribution<> dis_key(0, 100000000);
    HashTable * table = new HashTable(5);

    /*指定3条数据,验证是否正确*/
    table->HashAdd(666, 123);
    table->HashAdd(32155, 12345);
    table->HashAdd(6668989, 1234567);

    try
    {
        cout << "开始数据插入......" << endl;
        for (int i = 0; i < 20000000; ++i)
        {
            table->HashAdd(dis_key(engine), i);
        }
        cout << "数据插入完成！" << endl;
    }
    catch (std::bad_alloc&)
    {
        cout << "内存分配失败(可能存在内存不足),程序中止！" << endl;
        delete table;
        table = NULL;
        system("pause");
        return 0;
    }
    
    auto begin = system_clock::now();
    cout << "开始数据查询......" << endl;
    /*查询2000万次*/
    for (int i = 0; i < 20000000; ++i)
    {
        table->HashLookup(i);
    }
    
    cout << "查询666:" << table->HashLookup(666) << endl;
    cout << "查询32155:" << table->HashLookup(32155) << endl;
    cout << "查询6668989:" << table->HashLookup(6668989) << endl;

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - begin);
    cout << "查询时间花费了：" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;
    
    delete table;
    table = NULL;
    system("pause");
    return 0;
}