#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../deque/deque.h"

namespace s21 {

class Queue {
 private:
  s21::deque<int> data_;

 public:
  Queue();
  Queue(size_t n);
  Queue(std::initializer_list<int> const& items);
  Queue(const Queue& l);
  Queue(Queue&& l) noexcept;
  ~Queue();

  Queue& operator=(Queue&& other) noexcept;
  Queue& operator=(const Queue& other);

  int Front();
  int Back();

  bool Empty();
  size_t Size();

  void Push(int value);
  void Pop();
};

}  // namespace s21

#endif