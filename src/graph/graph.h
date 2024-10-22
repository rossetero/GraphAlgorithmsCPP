#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <fstream>
#include <iostream>
#include <memory>

#include "t_matrix.h"

namespace s21 {

class Graph {
 public:
  Graph(Matrix<int>&& adjencyMatrix) : adjacency_matrix_(adjencyMatrix){};
  Graph() = default;

  Graph& operator=(const Graph& other) = default;
  Graph& operator=(Graph&& other) = default;

  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename) const;

  bool IsDirected() const;

  size_t order() const { return adjacency_matrix_.rows(); };

  const Matrix<int>& adjacency_matrix() const { return adjacency_matrix_; };

 private:
  Matrix<int> adjacency_matrix_;
  size_t numVertices;
};

}  // namespace s21

#endif