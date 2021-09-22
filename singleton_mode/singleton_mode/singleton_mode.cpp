// singleton_mode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "singleton_mode.h"

void SingletionMode::test() {
  std::cout << "test" << std::endl;
}

//0=饿汉 1=懒汉
#define MODE 1

#if MODE
SingletionMode* SingletionMode::p_singletion = nullptr;
SingletionMode* SingletionMode::GetInstance() {
  if (p_singletion == nullptr) {
    std::lock_guard<std::mutex> lock(m_mutex);
    p_singletion = new SingletionMode();
  }
  return  p_singletion;
}
#endif

int main() {
  SingletionMode* test = SingletionMode::GetInstance();
  test->test();
  return 0;
}

#if !MODE

SingletionMode* SingletionMode::p_singletion = new SingletionMode();

SingletionMode* SingletionMode::GetInstance() {
  return p_singletion;
}

#endif

