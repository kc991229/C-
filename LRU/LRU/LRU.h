#pragma once
#include <iostream>
#include <unordered_map>
///*
//* Least Recently Used
//* ˫������+��ϣ��ʵ��
//*/
//
//struct LinkNode {
//  LinkNode* next_;
//  LinkNode* prve_;
//  int key_, val_;
//  LinkNode() :next_(nullptr), prve_(nullptr), key_(0), val_(0) {}
//  LinkNode(int key, int val) :next_(nullptr), prve_(nullptr), key_(key), val_(val) {}
//};
//
//class LRU {
//public:
//  LRU(int capacity) :capacity_(capacity) {
//    size_ = 0;
//    head_ = new LinkNode();
//    tail_ = new LinkNode();
//    head_->next_ = tail_;
//    tail_->prve_ = head_;
//  }
//
//  int Get(int key){
//
//  }
//
//  void Put(int key,int val){
//    //1.count in hashmap?
//    if (mp_.count(key)) {
//      LinkNode* node = mp_[key];
//      MoveToHead(node);
//    } else {
//      LinkNode* node = new LinkNode(key, val);
//      InsertToHead(node);
//      if (size_ > capacity_) {
//        RemoveTail();
//      }
//    }
//  }
//
//private:
//  void MoveToHead(LinkNode* node) {
//    tail_->prve_ = node->prve_;
//    node->prve_->next_ = tail_;
//    head_->next_->prve_ = node;
//    node->next_ = head_->next_;
//    node->prve_ = head_;
//    head_->next_ = node;
//  }
//  void InsertToHead(LinkNode* node) {
//    head_->next_->prve_ = node;
//    node->next_ = head_->next_;
//    node->prve_ = head_;
//    head_->next_ = node;
//    size_++;
//  }
//  void RemoveTail() {
//    size_--;
//    tail_->prv
//  }
//  int capacity_;
//  int size_;
//  LinkNode* head_;
//  LinkNode* tail_;
//  std::unordered_map<int, LinkNode*> mp_;
//};
struct DLinkedNode {
  int key, value;
  DLinkedNode* prev;
  DLinkedNode* next;
  DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
  DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
  std::unordered_map<int, DLinkedNode*> cache;
  DLinkedNode* head;
  DLinkedNode* tail;
  int size;
  int capacity;

public:
  LRUCache(int _capacity) : capacity(_capacity), size(0) {
    // ʹ��αͷ����αβ���ڵ�
    head = new DLinkedNode();
    tail = new DLinkedNode();
    head->next = tail;
    tail->prev = head;
  }

  int Get(int key) {
    if (!cache.count(key)) {
      return -1;
    }
    // ��� key ���ڣ���ͨ����ϣ��λ�����Ƶ�ͷ��
    DLinkedNode* node = cache[key];
    moveToHead(node);
    return node->value;
  }

  void Put(int key, int value) {
    if (!cache.count(key)) {
      // ��� key �����ڣ�����һ���µĽڵ�
      DLinkedNode* node = new DLinkedNode(key, value);
      // ��ӽ���ϣ��
      cache[key] = node;
      // �����˫�������ͷ��
      addToHead(node);
      ++size;
      if (size > capacity) {
        // �������������ɾ��˫�������β���ڵ�
        DLinkedNode* removed = removeTail();
        // ɾ����ϣ���ж�Ӧ����
        cache.erase(removed->key);
        // ��ֹ�ڴ�й©
        delete removed;
        --size;
      }
    } else {
      // ��� key ���ڣ���ͨ����ϣ��λ�����޸� value�����Ƶ�ͷ��
      DLinkedNode* node = cache[key];
      node->value = value;
      moveToHead(node);
    }
  }

  void addToHead(DLinkedNode* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
  }

  void removeNode(DLinkedNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void moveToHead(DLinkedNode* node) {
    removeNode(node);
    addToHead(node);
  }

  DLinkedNode* removeTail() {
    DLinkedNode* node = tail->prev;
    removeNode(node);
    return node;
  }
};
