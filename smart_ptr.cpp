#include <iostream>
#include <memory>
#include <thread>
#include <functional>
#include <vector>
using namespace std;

template<typename T>
class RefCnt
{
public:
	RefCnt(T *ptr = nullptr) : mptr(ptr)
	{
		if (mptr != nullptr)
			mcount = 1;
	}

	void addRef() { mcount++; }	// 增加资源引用计数

	int delRef() { return --mcount; }

private:
	T *mptr;
	int mcount;
};

template<typename T>
class CSmartPtr
{
public:
	CSmartPtr(T *ptr = nullptr) : mptr(ptr) 
    {
		mpRefCnt = new RefCnt<T>(mptr);
    }

	~CSmartPtr() 
    {
		if (0 == mpRefCnt->delRef())
		{
			cout << "relase" << endl;
			delete mptr;
			mptr = nullptr;
		}
    };
	
	T& operator*() { return *mptr; }

	T* operator->() { return mptr; }

	CSmartPtr(const CSmartPtr<T> &src) : mptr(src.mptr), mpRefCnt(src.mpRefCnt)
	{
		if (mptr != nullptr)
			mpRefCnt->addRef();
	}

	CSmartPtr<T>& operator=(const CSmartPtr<T> &src)
	{
		if (this == &src)
			return *this;
		
		if (mpRefCnt->delRef() == 0)
		{
			delete mptr;
		}
		
		mptr = src.mptr;
		mpRefCnt = src.mpRefCnt;
		mpRefCnt->addRef();
		return *this;
	}

private:
	T *mptr;	// 指向资源的指针
	RefCnt<T> *mpRefCnt;	// 指向该资源引用计数对象的指针
};

class A
{
public:
	A()
	{
		cout << "A()" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}

	
};
class C
{
public:
	C()
	{
		cout << "C()" << endl;
	}
	~C()
	{
		cout << "~C()" << endl;
	}


CSmartPtr<A> a = CSmartPtr<A>(new A());
};

int main()
{
	C c;
	cout << "--------" << endl;
	return 0;
}
