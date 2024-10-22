#ifndef QUEUE_CC
#define QUEUE_CC

#include "queue.h"

namespace s21 {

Queue::Queue() : data_() {}

Queue::Queue(size_t n) : data_(n) {}

Queue::Queue(std::initializer_list<int> const& items) : data_(items.size()) {
  for (typename std::initializer_list<int>::iterator i = items.begin();
       i != items.end(); ++i) {
    Push(*i);
  }
}

Queue::Queue(const Queue& other) : data_(other.data_) {}

Queue::Queue(Queue&& other) noexcept : data_(std::move(other.data_)) {}

Queue::~Queue() {}

Queue& Queue::operator=(Queue&& other) noexcept {
  data_ = std::move(other.data_);
  return *this;
}

Queue& Queue::operator=(const Queue& other) {
  data_ = other.data_;
  return *this;
}

int Queue::Front() { return *(data_.back()); }

int Queue::Back() { return *(data_.front()); }

bool Queue::Empty() { return data_.empty(); }

size_t Queue::Size() { return data_.size(); }

void Queue::Push(int value) { data_.push_front(value); }

void Queue::Pop() { data_.pop_back(); }

}  // namespace s21

#endif