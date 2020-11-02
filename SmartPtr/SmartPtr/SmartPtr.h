#pragma once

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
//RAII˼��
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
		//���������
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
		//����Ȩת��
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
				if (_ptr)//�ͷ�ԭ���Ŀռ�
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

		//�������岻֧�ֿ��������=
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
			//������Դ�ĳ�Ա����1
			(*_count)++;
		}

		shared_ptr<T>& operator =(shared_ptr<T>& ap)
		{
			if (this != &ap)
			{
				//��ͬ������Դ
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
	// ���ü��������Կ���
	// ȱ�ݣ�ѭ������
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
				// �������ü���������������һ��������Դ�Ķ������ͷ���Դ
				release();

				// �ҿ�ʼ����һ�������Դ
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

	// �ϸ���˵weak_ptr��������ָ�룬��Ϊ��û��RAII��Դ�������
	// ר�Ž��shared_ptr��ѭ����������
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