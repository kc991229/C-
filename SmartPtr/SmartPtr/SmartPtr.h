#pragma once

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
//RAII思想
namespace RAII
{
	template <class T>
	class SmartPtr
	{
	public:
		SmartPtr( T* ptr = nullptr)
			:_ptr(ptr)
		{}
		~SmartPtr()
		{
			delete _ptr;
			_ptr = nullptr;
			std::cout << "delete _ptr" << std::endl;
		}
		//重载运算符
		T* operator ->()
		{
			return _ptr;
		}
		T& operator *()
		{
			return *_ptr;
		}
	private:
		T* _ptr;
	};
}
namespace SmartPtr
{
	template <class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{}
		//管理权转移
		auto_ptr(auto_ptr<T>& ptr)
			:_ptr(ptr)
		{
			ptr._ptr = nullptr;
		}
		~auto_ptr()
		{
			delete _ptr;
			_ptr = nullptr;
			cout << "delete _ptr" << std::endl;
		}
		auto_ptr<T>& operator =(auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr)//释放原来的空间
					delete _ptr;
				_ptr = ptr._ptr;
				ap._ptr = nullptr;
			}
			return *this;
		}
		T& operator *()
		{
			return _ptr;
		}
		T* operator ->()
		{
			return *_ptr;
		}
	private:
		T* _ptr;
	};

	template <class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr = nullptr)
			:_ptr(ptr)
		{}
		~unique_ptr()
		{
			delete _ptr;
			_ptr = nullptr;
		}

		//暴力定义不支持拷贝构造和=
		unique_ptr(unique_ptr<T>& ap) = delete;
		unique_ptr<T>& operator=(unique_ptr<T>& ap) = delete;

		T& operator *()
		{
			return _ptr;
		}
		T* operator ->()
		{
			return *_ptr;
		}
	private:
		T* _ptr;
	};

	template <class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			:_ptr(ptr)
			, *_count(1)
		{}

		shared_ptr(shared_ptr<T>& ap)
			:_ptr(ap._ptr)
			,_count(ap._count)
		{
			//管理资源的成员数加1
			(*_count)++;
		}

		shared_ptr<T>& operator =(shared_ptr<T>& ap)
		{
			if (this != &ap)
			{
				//共同管理资源
				_ptr = ap._ptr;
				_count = ap._count;
				(*_count)++;
			}
			return *this;
		}

		~shared_ptr()
		{
			if (--(*_count) == 0)
			{
				delete _ptr;
				delete _count;
				_ptr = nullptr;
				_count = nullptr;
				std::cout << "delete shared_ptr" << std::endl;
			}
			else
			{
				_ptr = nullptr;
				_count = nullptr;
			}
		}
		T& operator *()
		{
			return _ptr;
		}
		T* operator ->()
		{
			return *_ptr;
		}
	private:
		T* _ptr;
		int* _count;
	};
}

namespace shared_ptr
{
	// C++11  shared_ptr
	// 引用计数，可以拷贝
	// 缺陷：循环引用
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			:_ptr(ptr)
			, _pcount(new int(1))
			, _pmtx(new mutex)
		{}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pcount(sp._pcount)
			, _pmtx(sp._pmtx)
		{
			add_ref_count();
		}

		// sp1 = sp4
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 减减引用计数，如果我是最后一个管理资源的对象，则释放资源
				release();

				// 我开始跟你一起管理资源
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				_pmtx = sp._pmtx;

				add_ref_count();
			}

			return *this;
		}

		void add_ref_count()
		{
			_pmtx->lock();

			++(*_pcount);

			_pmtx->unlock();
		}

		void release()
		{
			bool flag = false;

			_pmtx->lock();
			if (--(*_pcount) == 0)
			{
				if (_ptr)
				{
					cout << "delete:" << _ptr << endl;
					delete _ptr;
					_ptr = nullptr;
				}

				delete _pcount;
				_pcount = nullptr;
				flag = true;
			}
			_pmtx->unlock();

			if (flag == true)
			{
				delete _pmtx;
				_pmtx = nullptr;
			}
		}


		~shared_ptr()
		{
			release();
		}

		int use_count()
		{
			return *_pcount;
		}

		T* get_ptr() const
		{
			return _ptr;
		}

		T& operator *()
		{
			return *_ptr;
		}

		T* operator ->()
		{
			return _ptr;
		}
	private:
		int* _pcount;
		T* _ptr;
		mutex* _pmtx;
	};

	// 严格来说weak_ptr不是智能指针，因为他没有RAII资源管理机制
	// 专门解决shared_ptr的循环引用问题
	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr() = default;

		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get_ptr())
		{}

		weak_ptr<T>& operator = (const shared_ptr<T>& sp)
		{
			_ptr = sp.get_ptr();

			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

	private:
		T* _ptr;
	};
}