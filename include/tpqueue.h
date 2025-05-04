// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* link;
    explicit Node(const T& input) : data(input), link(nullptr) {}
  };

  Node* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head) {
      Node* temp = head;
      head = head->link;
      delete temp;
    }
  }

  void push(const T& element) {
    Node* newNode = new Node(element);
    if (!head) {
      head = newNode;
      return;
    }
    if (element.prior > head->data.prior) {
      newNode->link = head;
      head = newNode;
      return;
    }
    Node* iterator = head;
    while (iterator->link && iterator->link->data.prior >= element.prior) {
      iterator = iterator->link;
    }
    newNode->link = iterator->link;
    iterator->link = newNode;
  }

  T pop() {
    if (!head) {
      throw std::out_of_range("Queue is empty!");
    }
    Node* removeNode = head;
    T returnValue = head->data;
    head = head->link;
    delete removeNode;
    return returnValue;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
