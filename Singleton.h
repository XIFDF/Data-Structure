#pragma once
using namespace std;

template<typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}

	Singleton(T&&) = delete;
	Singleton(const T&) = delete;
	void operator= (const T&) = delete;

protected:
	virtual ~Singleton() = default;
	Singleton() = default;

};

