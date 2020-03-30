#include <iostream>
using namespace std;

class Date
{
public:
	void Print(Date& d)
	{
		cout << d._year << "-" << d._month << "-" << d._day << endl;
	}
	int getmonthday(int _year, int _day)
	{
		static int day[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int daynum = day[_day];
		if (_year % 4 == 0 && _year % 100 != 0 && _year % 400 == 0)
		{
			daynum++;
		}
		return daynum;
	}
	int getyeardays(int year)
	{
		if (getmonthday(year, 2) == 29)
			return 366;
		else
			return 365;
	}
	int getmodulus(int num)
	{
		if (num<0)
			num = -num;
		return num;
	}
	// 全缺省的构造函数
	Date(int year = 1900, int month = 1, int day = 1)
	{
		if (year > 0 && month >0 && month < 13 && day < getmonthday(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "非法日期" << endl;
		}
	}
	//拷贝构造函数
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	// 赋值运算符重载
	// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}
	// 日期+=天数
	Date& operator+=(int day)
	{
		if (day<0)
		{
			*this -= day;
			return *this;
		}
		_day += day;
		while (_day > getmonthday(_year, _month))
		{
			_month++;
			_day -= getmonthday(_year, _month);
			if (_month == 13)
			{
				_month = 1;
				_year++;
			}
		}
		return *this;
	}
	// 日期+天数
	Date operator+(int day)
	{
		Date ret(*this);
		ret += day;
		return ret;
	}
	// 日期-天数
	Date operator-(int day)
	{
		Date ret(*this);
		ret -= day;
		return ret;
	}
	// 日期-=天数
	Date& operator-=(int day)
	{
		if (day < 0)
		{
			*this += day;
			return *this;
		}
		_day -= day;
		while (_day < 1)
		{
			_month--;
			if (_month < 1)
			{
				_year--;
				_month = 12;
			}
			_day += getmonthday(_year, _month);
		}
		return *this;
	}
	// 日期-日期 返回天数
	int operator-(const Date& b)
	{
		int D_value = 0;
		Date d(b);
		Date e(*this);
		if ((d._year > e._year) || ((e._year == d._year) && (e._month < d._month))
			|| ((e._year == d._year) && (e._month == d._month) && (e._day < d._day)))
		{
			cout << "非法操作" << endl;
			return -1;
		}
		if (e._year == d._year)
		{
			if (e._month == d._month)
				return e._day - d._day;
			else
			{
				while (d._month != e._month)
				{
					D_value += getmonthday(e._year, d._month);
					d._month++;
				}
				return D_value + getmodulus(e._day - d._day);
			}
		}
		else
		{
			while (e._year - d._year != 1)
			{
				if (getmonthday(d._year, 2) == 28)
					D_value += 365;
				else
					D_value += 366;
				d._year++;
			}
			while ((e._year != d._year)||(e._month >= d._month))
			{
				D_value += getmonthday(d._year, d._month);
				d += getmonthday(d._year, d._month);
			}
			if (e._day > d._day)
				return D_value + e._day - d._day;
			else
				return D_value + d._day - e._day;
		}
	}
	// 前置++
	Date& operator++()
	{
		*this += 1;
		return *this;
	}
	// 后置++
	Date operator++(int)
	{
		Date ret(*this);
		++(*this);
		return ret;
	}
	// 后置--
	Date operator--(int)
	{
		Date ret(*this);
		*this -=1;
		return ret;
	}
	// 前置--
	Date& operator--()
	{
		*this -= 1;;
		return *this;

	}
	// >运算符重载
	bool operator>(const Date& d)
	{
		if ((_year > d._year)
			|| (_year == d._year && _month > d._month)
			|| (_year == d._year && _month == d._month && _day > d._day))
		{
			return true;
		}

		return false;
	}
	// ==运算符重载
	bool operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;

	}
	// >=运算符重载
	inline bool operator >= (const Date& d)
	{
		if ((_year > d._year) || (_year == d._year) && (_month < d._month)
			|| (_year == d._year) && (_month == d._month) && (_day >= d._day))
		{
			return true;
		}
		return false;
	}

	// <运算符重载
	bool operator < (const Date& d)
	{
		if ((_year < d._year)
			|| (_year == d._year && _month < d._month)
			|| (_year == d._year && _month == d._month && _day < d._day))
		{
			return true;
		}

		return false;
	}
	// <=运算符重载
	bool operator <= (const Date& d)
	{
		if ((_year < d._year)
			|| (_year == d._year && _month < d._month)
			|| (_year == d._year && _month == d._month && _day <= d._day))
		{
			return true;
		}
		return false;
	}
	// !=运算符重载
	bool operator != (const Date& d)
	{
		return !(_year == d._year && _month == d._month && _day == d._day);
	}
private:
	int _year;
	int _month;
	int _day;
};