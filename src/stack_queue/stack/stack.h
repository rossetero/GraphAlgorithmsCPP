#ifndef S21_STACK_H
#define S21_STACK_H

#include "../deque/deque.h"

namespace s21 {

class Stack {
 private:
  s21::deque<int> data_;

 public:
  Stack();
  Stack(std::initializer_list<int> const& items);
  Stack(const Stack& l);
  Stack(Stack&& l) noexcept;
  ~Stack();

  Stack& operator=(Stack&& other) noexcept;
  Stack& operator=(const Stack& other);

  bool operator==(const Stack& other) const;
  bool operator!=(const Stack& other) const;

  int Top() const;

  bool Empty() const;
  int Size() const;

  void Push(int value);
  void Pop();
};

}  // namespace s21

#endif