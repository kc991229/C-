#include <iostream>
#include <set>
#include <map>
#include <string>
using namespace std;

void text1()
{
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));
	cout << s.size() << endl;
}
void text2()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));
	set<int>::iterator it = s.begin();
	for (; it != s.end(); it++)
		cout << *it << "  ";
	cout << endl;
	for (auto v : s)
		cout << v << "  ";
}
void text3()
{
	int arr[] = { 0, 1, 3, 2, 5, 4, 6, 7 };
	set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));
	//set进行了排序
	for (auto v : s)
		cout << v << "  ";
	cout << endl;
	//插入
	pair<set<int>::iterator, bool> a = s.insert(8);
	for (auto v : s)
		cout << v << "  ";
	cout << endl;
	//删除
	s.erase(a.first);
	for (auto v : s)
		cout << v << "  ";
	cout << endl;
	s.erase(1);
	for (auto v : s)
		cout << v << "  ";
	cout << endl;
	//
}
void text4()
{
	map<int, string> num;
	num.insert(make_pair(1, "one"));
	num[2] = "two";
	num[3] = "three";
	num.insert(make_pair(4, "four"));
	for (auto& v : num)
		cout << v.first << "->" << v.second << "  ";
	cout << endl;
}
void text5()
{
	map<string, string> d;
	d["apple"] = "苹果";
	d["ruler"] = "尺子";
	d["banane"] = "香蕉";
	map<string, string>::iterator it = d.begin();
	while (it != d.end())
	{
		cout << (*it).first << ":" << (*it).second << "  ";
		it++;
	}
	cout << endl;
}
int main()
{
	//text1();
	//text2();
	//text3();
	//text4();
	text5();
	return 0;
}