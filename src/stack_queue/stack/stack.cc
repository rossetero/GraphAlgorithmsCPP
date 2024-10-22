#ifndef STACK_CC
#define STACK_CC

#include "stack.h"

namespace s21 {

Stack::Stack() : data_() {}

Stack::Stack(std::initializer_list<int> const& items) : data_(items.size()) {
  for (typename std::initializer_list<int>::iterator i = items.begin();
       i != items.end(); ++i) {
    Push(*i);
  }
}

Stack::Stack(const Stack& other) : data_(other.data_) {}

Stack::Stack(Stack&& other) noexcept : data_(std::move(other.data_)) {}

Stack::~Stack() {}

Stack& Stack::operator=(Stack&& other) noexcept {
  data_ = std::move(other.data_);
  return *this;
}

Stack& Stack::operator=(const Stack& other) {
  data_ = other.data_;
  return *this;
}

bool Stack::operator==(const Stack& other) const {
  return data_ == other.data_;
}

bool Stack::operator!=(const Stack& other) const {
  return data_ != other.data_;
}

int Stack::Top() const { return *(data_.front()); }

bool Stack::Empty() const { return data_.empty(); }

int Stack::Size() const { return data_.size(); }

void Stack::Push(const int value) { data_.push_front(value); }

void Stack::Pop() { data_.pop_front(); }

}  // namespace s21

#endif