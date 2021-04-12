#include <gtest/gtest.h>
#include "Singleton.h"
#include <iostream>
#include <thread>
#include <sstream>
using namespace std;

#define MYA SingletonA::GetInstance()
stringstream ss1, ss2;
class SingletonA : public Singleton<SingletonA>
{
public:
	void UsingA()
	{
		cout << &GetInstance() << endl;
	}
};
void proc1()
{
	MYA.UsingA();
	ss1 << &MYA;
}

void proc2()
{
	MYA.UsingA();
	ss2 << &MYA;
}

TEST(SingleonTest, get_result)
{
	thread t1(proc1);
	thread t2(proc2);
	t1.join();
	t2.join();
	string str1(ss1.str());
	string str2(ss2.str());
	ASSERT_STREQ(str1.data(), str2.data());
}

