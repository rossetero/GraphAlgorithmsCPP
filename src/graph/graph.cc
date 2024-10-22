#include "graph.h"

namespace s21 {

void Graph::LoadGraphFromFile(const std::string& filepath) {
  std::ifstream f(filepath);
  if (!f) {
    throw std::runtime_error("Unable to open file with matrix");
  }

  int order;
  f >> order;
  if (f.fail() || order <= 0) {
    throw std::runtime_error("Invalid order value in file");
  }

  Matrix<int> adjacency_matrix(order, order);
  for (int i = 0; i < order; i++) {
    for (int j = 0; j < order; j++) {
      f >> adjacency_matrix(i, j);
      if (f.fail()) {
        throw std::runtime_error("Failed to read matrix element at (" +
                                 std::to_string(i) + ", " + std::to_string(j) +
                                 ")");
      }
    }
  }

  adjacency_matrix_ = std::move(adjacency_matrix);
  f.close();
}

bool Graph::IsDirected() const {
  for (size_t i = 0; i < order(); i++) {
    for (size_t j = i + 1; j < order(); j++) {
      if (adjacency_matrix_(i, j) != adjacency_matrix_(j, i)) {
        return true;
      }
    }
  }
  return false;
}

void Graph::ExportGraphToDot(const std::string& filename) const {
  std::ofstream outfile(filename);
  if (!outfile) {
    throw std::runtime_error("Unable to write in DOT file");
  }

  bool directed = IsDirected();

  std::string title = directed ? "digraph G {" : "graph G {";
  outfile << title << std::endl;
  std::string dash = directed ? " -> " : " -- ";
  for (size_t i = 0; i < order(); ++i) {
    size_t j = directed ? 0 : i;
    for (; j < order(); ++j) {
      if (adjacency_matrix_(i, j) == 1) {
        outfile << "\t" << i << dash << j
                << " [weight=" << adjacency_matrix_(i, j) << "];" << std::endl;
      } else if (adjacency_matrix_(i, j) != 0) {
        outfile << "\t" << i << dash << j
                << " [label=" << adjacency_matrix_(i, j) << "];" << std::endl;
      }
    }
  }

  outfile << "}" << std::endl;
  outfile.close();
}

}  // namespace s21