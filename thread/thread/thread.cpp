#include <iostream>
#include <thread>

using namespace std;

void ThreadFunc(int a) {
	cout << "Thread1" << a << endl;
}
class TF
{
public:
	void operator()()
	{
		cout << "Thread3" << endl;
	}
};
int main()
{
	// 线程函数为函数指针
	thread t1(ThreadFunc, 10);

	// 线程函数为lambda表达式
	thread t2([]{cout << "Thread2" << endl; });

	// 线程函数为函数对象
	TF tf;
	thread t3(tf);

	t1.join();
	t2.join();
	t3.join();
	cout << "Main thread!" << endl;
	return 0;
}
