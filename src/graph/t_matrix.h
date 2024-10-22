#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <stdexcept>
#include <vector>

namespace s21 {
template <typename T>
class Matrix {
 public:
  Matrix() : rows_(0), cols_(0), data_() {}

  Matrix(size_t rows, size_t cols, const T &value = T())
      : rows_(rows), cols_(cols), data_(rows * cols, value) {
    if (rows == 0 || cols == 0) {
      throw std::invalid_argument(
          "Matrix dimensions must be greater than zero.");
    }
  }

  ~Matrix() = default;
  Matrix(const Matrix &other)
      : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {}

  Matrix &operator=(const Matrix &other) {
    if (this != &other) {
      rows_ = other.rows_;
      cols_ = other.cols_;
      data_ = other.data_;
    }
    return *this;
  }

  Matrix(Matrix &&other) noexcept
      : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
    other.rows_ = 0;
    other.cols_ = 0;
  }

  Matrix &operator=(Matrix &&other) noexcept {
    if (this != &other) {
      rows_ = other.rows_;
      cols_ = other.cols_;
      data_ = std::move(other.data_);
      other.rows_ = 0;
      other.cols_ = 0;
    }
    return *this;
  }

  T &operator()(size_t row, size_t col) {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Matrix subscript out of range.");
    }
    return data_[row * cols_ + col];
  }

  const T &operator()(size_t row, size_t col) const {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Matrix subscript out of range.");
    }
    return data_[row * cols_ + col];
  }

  size_t rows() const { return rows_; }
  size_t cols() const { return cols_; }

  void print() const {
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < cols_; j++) {
        std::cout << this->operator()(i, j) << " ";
      }
      std::cout << std::endl;
    }
  }
  void setResize(size_t sz) {
    rows_ = sz;
    cols_ = sz;
    data_.resize(sz * sz);
  }

  bool EqVector(const std::vector<int> &other) const noexcept {
    int eq = true;
    for (size_t i = 0; i < rows_ && eq; ++i) {
      for (size_t j = 0; j < cols_ && eq; ++j) {
        if ((*this)(i, j) != other[i * cols_ + j]) {
          eq = false;
        }
      }
    }
    return eq;
  }

 private:
  size_t rows_;
  size_t cols_;
  std::vector<T> data_;
};

}  // namespace s21

#endif
