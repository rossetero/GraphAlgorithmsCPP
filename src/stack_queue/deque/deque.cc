#ifndef S21_DEQUE_CPP
#define S21_DEQUE_CPP

#include "deque.h"

namespace s21 {

template <typename T>
deque<T>::iterator::iterator() : buckets_(nullptr), index_(0U) {}

template <typename T>
deque<T>::iterator::iterator(const iterator& other)
    : buckets_(other.buckets_), index_(other.index_) {}

template <typename T>
deque<T>::iterator::iterator(iterator&& other) noexcept
    : buckets_(other.buckets_), index_(other.index_) {
  other.buckets_ = nullptr;
  other.index_ = 0U;
}

template <typename T>
deque<T>::iterator::iterator(T** bucketsPointer, size_t index)
    : buckets_(bucketsPointer), index_(index) {}

template <typename T>
typename deque<T>::iterator& deque<T>::iterator::operator=(
    const iterator& other) {
  this->buckets_ = other.buckets_;
  this->index_ = other.index_;
  return *this;
}

template <typename T>
typename deque<T>::iterator& deque<T>::iterator::operator++() {
  ++index_;
  return *this;
}

template <typename T>
typename deque<T>::iterator& deque<T>::iterator::operator--() {
  --index_;
  return *this;
}

template <typename T>
T& deque<T>::iterator::operator*() {
  return buckets_[index_ / bucketSize][index_ % bucketSize];
}

template <typename T>
const T& deque<T>::iterator::operator*() const {
  return buckets_[index_ / bucketSize][index_ % bucketSize];
}

template <typename T>
bool deque<T>::iterator::operator==(const iterator& other) const noexcept {
  return buckets_ == other.buckets_ && index_ == other.index_;
}

template <typename T>
bool deque<T>::iterator::operator!=(const iterator& other) const noexcept {
  return buckets_ != other.buckets_ || index_ != other.index_;
}

template <typename T>
deque<T>::deque(size_type n)
    : buckets_(new T*[(n / bucketSize) + 1]),
      size_(0U),
      bucketsCount_((n / bucketSize) + 1),
      startIndex_((bucketsCount_ / 2) * bucketSize + 1U),
      finishIndex_(startIndex_) {
  for (size_type i = 0; i < bucketsCount_; ++i) {
    buckets_[i] = static_cast<T*>(operator new(bucketSize * sizeof(T)));
  }
}

template <typename T>
deque<T>::deque() : deque(0U) {}

template <typename T>
deque<T>::deque(std::initializer_list<T> const& items) : deque(items.size()) {
  for (typename std::initializer_list<T>::iterator i = items.begin();
       i != items.end(); ++i) {
    this->push_back(*i);
  }
}

template <typename T>
deque<T>::deque(const deque& other)
    : buckets_(new T*[other.bucketsCount_]),
      size_(0U),
      bucketsCount_(other.bucketsCount_),
      startIndex_((bucketsCount_ / 2) * bucketSize + 1U),
      finishIndex_(startIndex_) {
  for (size_type i = 0; i < bucketsCount_; ++i) {
    buckets_[i] = static_cast<T*>(operator new(bucketSize * sizeof(T)));
  }

  for (size_type i = 0; i < other.size_; ++i) {
    this->push_back(other[i]);
  }
}

template <typename T>
deque<T>::deque(deque&& other) noexcept
    : buckets_(other.buckets_),
      size_(other.size_),
      bucketsCount_(other.bucketsCount_),
      startIndex_(other.startIndex_),
      finishIndex_(other.finishIndex_) {
  other.buckets_ = nullptr;
  other.size_ = 0U;
  other.bucketsCount_ = 0;
  other.startIndex_ = 1;
  other.finishIndex_ = 1;
}

template <typename T>
deque<T>::~deque() {
  if (buckets_ == nullptr) {
    return;
  }

  for (size_type i = 0; i < size_; ++i) {
    (&((*this)[i]))->~T();
  }

  for (size_type bucketInd = 0; bucketInd < bucketsCount_; ++bucketInd) {
    operator delete(buckets_[bucketInd]);
  }

  delete[] buckets_;
}

template <typename T>
typename deque<T>::deque& deque<T>::operator=(deque&& other) noexcept {
  if (this == &other) return other;

  if (buckets_ != nullptr) {
    for (size_type i = 0; i < size_; ++i) {
      (&((*this)[i]))->~T();
    }

    for (size_type bucketInd = 0; bucketInd < bucketsCount_; ++bucketInd) {
      operator delete(buckets_[bucketInd]);
    }

    delete[] buckets_;
  }

  this->buckets_ = other.buckets_;
  this->size_ = other.size_;
  this->bucketsCount_ = other.bucketsCount_;
  this->startIndex_ = other.startIndex_;
  this->finishIndex_ = other.finishIndex_;

  other.buckets_ = nullptr;
  other.size_ = 0U;
  other.bucketsCount_ = 0;
  other.startIndex_ = 1;
  other.finishIndex_ = 1;
  return *this;
}

template <typename T>
bool deque<T>::operator==(const deque& other) const {
  if ((finishIndex_ - startIndex_) !=
      (other.finishIndex_ - other.startIndex_)) {
    return false;
  }

  bool isEqual = true;

  deque<T>::iterator i = this->begin();
  deque<T>::iterator j = other.begin();

  while (i != this->end() && j != other.end()) {
    if (*i != *j) {
      isEqual = false;
      break;
    }
    ++i;
    ++j;
  }

  return isEqual;
}

template <typename T>
bool deque<T>::operator!=(const deque& other) const {
  return !(*this == other);
}

template <typename T>
typename deque<T>::deque& deque<T>::operator=(const deque& other) {
  deque<T> tmp = other;

  if (buckets_ != nullptr) {
    *this = std::move(tmp);
  }

  return *this;
}

template <typename T>
typename deque<T>::size_type deque<T>::size() const {
  return size_;
}

template <typename T>
[[nodiscard]] bool deque<T>::empty() const {
  return size_ == 0;
}

template <typename T>
T& deque<T>::operator[](size_type index) const {
  return buckets_[(startIndex_ + 1 + index) / bucketSize]
                 [(startIndex_ + 1 + index) % bucketSize];
}

template <typename T>
typename deque<T>::iterator deque<T>::front() const {
  iterator frontIterator(buckets_, startIndex_ + 1);
  return frontIterator;
}

template <typename T>
typename deque<T>::iterator deque<T>::back() const {
  iterator backIterator(buckets_, finishIndex_ - 1);
  return backIterator;
}

template <typename T>
typename deque<T>::iterator deque<T>::begin() const {
  typename deque<T>::iterator iteratorBegin(buckets_, startIndex_ + 1);
  return iteratorBegin;
}

template <typename T>
typename deque<T>::iterator deque<T>::end() const {
  typename deque<T>::iterator iteratorEnd(buckets_, finishIndex_);
  return iteratorEnd;
}

template <typename T>
void deque<T>::push_back(const_reference value) {
  if (finishIndex_ == bucketsCount_ * bucketSize - 1) {
    this->reallocate();
  }

  if (finishIndex_ == startIndex_) {
    --startIndex_;
  }

  new (this->buckets_[finishIndex_ / bucketSize] + (finishIndex_ % bucketSize))
      T(value);

  finishIndex_++;
  size_ = finishIndex_ - startIndex_ - 1;
}
template <typename T>
void deque<T>::pop_back() {
  (&((*this)[this->size() - 1]))->~T();
  --(this->size_);
  --(this->finishIndex_);
}

template <typename T>
void deque<T>::push_front(const_reference value) {
  if (startIndex_ == 0) {
    this->reallocate();
  }

  if (finishIndex_ == startIndex_) {
    ++finishIndex_;
  }

  new (&this->buckets_[startIndex_ / bucketSize][startIndex_ % bucketSize])
      T(value);
  --startIndex_;
  size_ = finishIndex_ - startIndex_ - 1;
}

template <typename T>
void deque<T>::pop_front() {
  (&((*this)[0]))->~T();
  --(this->size_);
  ++(this->startIndex_);
}

template <typename T>
void deque<T>::swap(deque& other) {
  std::swap(this->buckets_, other.buckets_);
  std::swap(this->bucketsCount_, other.bucketsCount_);
  std::swap(this->size_, other.size_);
  std::swap(this->startIndex_, other.startIndex_);
  std::swap(this->finishIndex_, other.finishIndex_);
}

template <typename T>
void deque<T>::reallocate() {
  size_type new_bucketsCount = 2 * bucketsCount_ + 1;
  size_type increase = (new_bucketsCount - bucketsCount_) / 2;
  size_type new_startIndex = increase * bucketSize + startIndex_;
  size_type new_finishIndex = increase * bucketSize + finishIndex_;
  T** new_buckets = new T*[new_bucketsCount];

  size_type index = 0;
  size_type counter = 0;
  try {
    while (counter < increase) {
      new_buckets[index++] =
          static_cast<T*>(operator new(bucketSize * sizeof(T)));
      ++counter;
    }

    counter = 0;
    while (counter < bucketsCount_) {
      new_buckets[index++] = buckets_[counter];
      ++counter;
    }

    counter = 0;
    while (counter < increase) {
      new_buckets[index++] =
          static_cast<T*>(operator new(bucketSize * sizeof(T)));
      ++counter;
    }

  } catch (...) {
    for (size_type j = 0; j < index; ++j) {
      if (index < increase || index > (increase + bucketsCount_)) {
        operator delete(new_buckets[index]);
      }
    }
    delete[] new_buckets;
    throw;
  }

  delete[] buckets_;

  bucketsCount_ = new_bucketsCount;
  startIndex_ = new_startIndex;
  finishIndex_ = new_finishIndex;
  buckets_ = new_buckets;
}
}  // namespace s21

#endif