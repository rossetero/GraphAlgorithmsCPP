#ifndef _ANT_COLONY_ALGORITHMS_H_
#define _ANT_COLONY_ALGORITHMS_H_

#include <algorithm>
#include <random>
#include <vector>

#include "graph.h"
#include "t_matrix.h"

namespace s21 {

class AntColonyAlgorithms {
 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  class Ant {
   public:
    std::vector<int> path;
    double distance = 0.0;

    void Launch(const Matrix<int>& adj_matrix,
                const Matrix<double>& pheromones);
    bool IsVisited(int vertex) const;
    int ChooseNextVertex(
        const std::vector<std::pair<int, double>>& probabilities);

   private:
    std::vector<std::pair<int, double>> CalculateProbabilities(
        int current_vertex, const Matrix<int>& adj_matrix,
        const Matrix<double>& pheromones);
    void NormalizeProbabilities(
        std::vector<std::pair<int, double>>& probabilities);
    void ResetPath(int start_vertex);
  };

  class Colony {
   public:
    Colony(size_t num_ants, const Matrix<int>& adjacency_matrix)
        : best_ant(Ant{std::vector<int>(), std::numeric_limits<double>::max()}),
          adjacency_matrix_(adjacency_matrix) {
      pheromones_ =
          Matrix<double>(adjacency_matrix.rows(), adjacency_matrix.cols(), 1.0);
      anthill_.resize(num_ants);
    }

    void DistributeAnts();
    void LaunchIteration();
    void UpdatePheromones();
    void UpdateBestPath(Ant& ant);

    Ant best_ant;

   private:
    Matrix<int> adjacency_matrix_;
    Matrix<double> pheromones_;
    std::vector<Ant> anthill_;
  };

  static TsmResult SolveTravelingSalesmanProblem(Graph& graph,
                                                 size_t iterations = 10,
                                                 size_t ants_on_vertex = 1);
};
}  // namespace s21
#endif