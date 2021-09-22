// LRU.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "LRU.h"
using namespace std;
int main()
{
  LRUCache lr(2);
  lr.Put(1, 1);
  lr.Put(2, 1);
  cout << lr.Get(1) << endl;
  lr.Put(3, 3);
  cout << lr.Get(2) << endl;
  lr.Put(4, 4);
  cout << lr.Get(1) << endl;
  cout << lr.Get(3) << endl;
  cout << lr.Get(4) << endl;
  return 0;
}

