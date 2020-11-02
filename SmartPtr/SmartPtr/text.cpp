#include "SmartPtr.h"
#include <memory>

//void text()
//{
//	RAII::SmartPtr<int> s(new int(1));
//}
//int main()
//{
//	std::auto_ptr<RAII::SmartPtr<int>> s(new RAII::SmartPtr<int>);
//	return 0;
//}
class Date
{
public:
	Date() { std::cout << "Date()" <<std:: endl; }
	~Date(){std:: cout << "~Date()" <<std:: endl; }
	int _year;
	int _month;
	int _day;
};
int main()
{
	std::auto_ptr<Date> ap(new Date);
	std::auto_ptr<Date> copy(ap);
	// auto_ptr�����⣺�����󿽱����߸�ֵ��ǰ��Ķ����������
	ap->_year = 2018;
	return 0;
}