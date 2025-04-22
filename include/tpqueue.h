// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <string>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T element;
    Node* nextNode;
    explicit Node(const T& val) : element(val), nextNode(nullptr) {}
  };

  Node* frontNode;

 public:
  TPQueue() : frontNode(nullptr) {}

  void push(const T& val) {
    Node* newNode = new Node(val);

    if (frontNode == nullptr || val.prior > frontNode->element.prior) {
      newNode->nextNode = frontNode;
      frontNode = newNode;
      return;
    }

    Node* traverse = frontNode;
    while (traverse->nextNode != nullptr && traverse->nextNode->element.prior >= val.prior) {
      traverse = traverse->nextNode;
    }

    newNode->nextNode = traverse->nextNode;
    traverse->nextNode = newNode;
  }

  T pop() {
    if (frontNode == nullptr) {
      throw std::string("Queue is empty");
    }

    Node* tempNode = frontNode;
    T returnValue = tempNode->element;
    frontNode = frontNode->nextNode;
    delete tempNode;
    return returnValue;
  }

  ~TPQueue() {
    while (frontNode != nullptr) {
      Node* toDelete = frontNode;
      frontNode = frontNode->nextNode;
      delete toDelete;
    }
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
