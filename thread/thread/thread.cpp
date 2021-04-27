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
	// �̺߳���Ϊ����ָ��
	thread t1(ThreadFunc, 10);

	// �̺߳���Ϊlambda���ʽ
	thread t2([]{cout << "Thread2" << endl; });

	// �̺߳���Ϊ��������
	TF tf;
	thread t3(tf);

	t1.join();
	t2.join();
	t3.join();
	cout << "Main thread!" << endl;
	return 0;
}
