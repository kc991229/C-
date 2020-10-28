#include <iostream>
#include <vector>
using namespace std;
int function(int x, int y)
{
	if (y == 0)
	{
		throw x;
	}
	else
		return x / y;
}
void test1()
{
	int i, j;
	cin >> i >> j;
	try
	{
		cout << function(i, j) << endl;
	}
	//catch (const char* errmsg)
	//{
	//	cout << errmsg << endl;
	//}
	//catch (const int errmsg)
	//{
	//	cout << errmsg << endl;
	//}
	//const exception& e
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "error" << endl;
	}
}
int main()
{
	try
	{
		vector<int> v(10, 5);
		// 这里如果系统内存不够也会抛异常
		v.reserve(1000000000);
		// 这里越界会抛异常
		v.at(10) = 100;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}
//int main()
//{
//	int i = 9, j = 0;
//	try
//	{
//		//i = i / j;
//		//throw i;
//		vector<int> v(10, 5);
//		// 这里如果系统内存不够也会抛异常
//		v.reserve(1000000000);
//		// 这里越界会抛异常
//		v.at(10) = 100;
//	}
//	catch (const exception& e) // 这里捕获父类对象就可以
//	{
//		cout << e.what() << endl;
//	}
//	catch (...)
//	{
//		cout << "Unkown Exception" << endl;
//	}
//	return 0;
//}