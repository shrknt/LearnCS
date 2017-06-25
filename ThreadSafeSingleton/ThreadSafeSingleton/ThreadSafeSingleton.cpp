#include<iostream>
#include<string>
#include<mutex>
using namespace std;

class Singleton
{
	Singleton() :data("I am the only one") {}
	Singleton(const Singleton&);
	Singleton(const Singleton&&);
	static Singleton* m_obj;
	string data;
	static mutex m_mtx;
public:
	static Singleton* Instance()
	{
		if (!m_obj)
		{
			m_mtx.lock();
			if(!m_obj)
				m_obj = new Singleton(); // This is still not thread safe as compiler can reorder construction and assignment though
			m_mtx.unlock();
		}
		return m_obj;
	}
	friend ostream& operator<<(ostream& out, const Singleton& s)
	{
		out << s.data;
		return out;
	}
};

Singleton* Singleton::m_obj = nullptr;
mutex Singleton::m_mtx;

int main1()
{
	cout << *Singleton::Instance() << endl;
	return 0;
}