#pragma once
#include <iostream>
#include <mutex>
class SingletionMode {
public:
  static SingletionMode* GetInstance();
  void test();
private:
  SingletionMode() {}
  SingletionMode(SingletionMode const&) = delete;
  SingletionMode& operator=(const SingletionMode&) = delete;
private:
  static SingletionMode* p_singletion;
  static std::mutex m_mutex;
};

