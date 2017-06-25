#include<iostream>
using namespace std;

template<class T>
class RefCntPtr
{
	T* m_p;
	size_t* m_refCount;
	void CheckAndDelete()
	{
		if (*m_refCount == 0)
		{
			delete m_p;
			delete m_refCount;
		}
	}
public:
	RefCntPtr(T* p) :m_p(p), m_refCount(new size_t(1)) {}
	RefCntPtr(const RefCntPtr<T>& oth) :m_p(oth.m_p), m_refCount(oth.m_refCount) 
	{
		++*m_refCount;
	}
	RefCntPtr<T>& operator=(const RefCntPtr<T>& oth)
	{
		++*oth.m_refCount;
		--*m_refCount;
		CheckAndDelete();
		m_refCount = oth.m_refCount;
		m_p = oth.m_p;
		return *this;
	}
	~RefCntPtr()
	{
		--*m_refCount;
		CheckAndDelete();
	}
	size_t RefCount() { return *m_refCount; }
};

class Test
{
	int i;
public:
	Test(int ii) :i(ii) { cout << "Test::Test() " << i << endl; }
	Test(const Test& t) : i(t.i) { cout << "Test::Test(const Test&) " << i << endl; }
	Test& operator=(const Test& t) { i = t.i; cout << "Test::operator=(const Test&) " << i << endl; }
	~Test() { cout << "Test::~Test() " << i << endl; }
};

int main()
{
	{
		RefCntPtr<Test> rptr1(new Test(100));
		RefCntPtr<Test> rptr2(new Test(200));
		RefCntPtr<Test> rptr3(new Test(300));
		RefCntPtr<Test> rptr4 = rptr1;
		rptr3 = rptr2;
		cout << rptr1.RefCount() << endl;
		cout << rptr2.RefCount() << endl;
		cout << rptr3.RefCount() << endl;
		cout << rptr4.RefCount() << endl;
	}
	return 0;
}