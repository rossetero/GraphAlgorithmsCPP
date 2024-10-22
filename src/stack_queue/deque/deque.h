#ifndef S21_DEQUE_H
#define S21_DEQUE_H

#include <cstddef>
#include <initializer_list>
#include <new>
#include <utility>

namespace s21 {

template <typename T>
class deque {
 public:
  class iterator {
   private:
    T** buckets_;
    size_t index_;

   public:
    iterator();
    iterator(const iterator& other);
    iterator(T** bucketsPointer, size_t index);
    iterator(iterator&& other) noexcept;
    ~iterator() = default;

    iterator& operator=(const iterator& other);
    iterator& operator==(iterator&& other);

    iterator& operator++();
    iterator& operator--();
    T& operator*();
    const T& operator*() const;

    bool operator==(const iterator& other) const noexcept;
    bool operator!=(const iterator& other) const noexcept;
  };

 private:
  T** buckets_;
  size_t size_;
  size_t bucketsCount_;
  size_t startIndex_;
  size_t finishIndex_;

 public:
  static const size_t bucketSize = 128U;

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using const_iterator = const iterator;
  using size_type = size_t;

  deque();
  deque(size_type n);
  deque(std::initializer_list<value_type> const& items);
  deque(const deque& l);
  deque(deque&& l) noexcept;
  ~deque();

  deque& operator=(deque&& other) noexcept;
  deque& operator=(const deque& other);
  bool operator==(const deque& other) const;
  bool operator!=(const deque& other) const;

  T& operator[](size_type index) const;
  iterator front() const;
  iterator back() const;

  iterator begin() const;
  iterator end() const;

  [[nodiscard]] bool empty() const;
  size_type size() const;

  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(deque& other);

 private:
  void reallocate();
};

};  // namespace s21

#include "deque.cc"
#endif