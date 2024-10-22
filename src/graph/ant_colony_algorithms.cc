#include "ant_colony_algorithms.h"

namespace s21 {
s21::AntColonyAlgorithms::TsmResult
s21::AntColonyAlgorithms::SolveTravelingSalesmanProblem(Graph& graph,
                                                        size_t iterations,
                                                        size_t ants_on_vertex) {
  size_t num_vertices = graph.order();
  Colony colony(num_vertices * ants_on_vertex, graph.adjacency_matrix());

  for (size_t i = 0; i < iterations; i++) {
    colony.LaunchIteration();
    colony.UpdatePheromones();
    colony.DistributeAnts();
  }

  return {colony.best_ant.path, colony.best_ant.distance};
}

void s21::AntColonyAlgorithms::Colony::DistributeAnts() {
  size_t num_vertices = pheromones_.rows();

  size_t i = 0;
  for (; i < num_vertices; i++) {
    anthill_[i].path.clear();
    anthill_[i].distance = 0;
    anthill_[i].path.push_back(i);
  }

  for (; i < anthill_.size(); i++) {
    anthill_[i].path.push_back(i % num_vertices);
  }
}

void s21::AntColonyAlgorithms::Colony::LaunchIteration() {
  for (Ant& ant : anthill_) {
    if (ant.path.size() == 1) {
      ant.Launch(adjacency_matrix_, pheromones_);
    }
    UpdateBestPath(ant);
  }
}

void s21::AntColonyAlgorithms::Colony::UpdatePheromones() {
  constexpr double ro = 0.66;

  for (size_t i = 0; i < pheromones_.rows(); i++) {
    for (size_t j = 0; j < pheromones_.cols(); j++) {
      pheromones_(i, j) *= ro;
    }
  }

  for (Ant& ant : anthill_) {
    if (ant.path.size() != adjacency_matrix_.rows()) {
      continue;
    }

    constexpr double q = 4;
    double delta_tau = q / ant.distance;

    for (size_t i = 0; i < ant.path.size() - 1; i++) {
      size_t from = ant.path[i];
      size_t to = ant.path[i + 1];
      pheromones_(from, to) += delta_tau;
    }
  }
}

void s21::AntColonyAlgorithms::Colony::UpdateBestPath(Ant& ant) {
  if (ant.path.size() == adjacency_matrix_.rows() &&
      ant.distance < best_ant.distance) {
    best_ant = ant;
  }
}

void s21::AntColonyAlgorithms::Ant::Launch(const Matrix<int>& adj_matrix,
                                           const Matrix<double>& pheromones) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  while (path.size() < adj_matrix.rows()) {
    int current_vertex = path.back();

    std::vector<std::pair<int, double>> probabilities =
        CalculateProbabilities(current_vertex, adj_matrix, pheromones);

    if (probabilities.empty()) {
      ResetPath(current_vertex);
      break;
    }

    NormalizeProbabilities(probabilities);

    int next_vertex = ChooseNextVertex(probabilities);
    if (next_vertex == -1) {
      ResetPath(current_vertex);
      break;
    }

    path.push_back(next_vertex);
    distance += adj_matrix(current_vertex, next_vertex);
  }

  if (path.size() == adj_matrix.rows() &&
      adj_matrix(path.back(), path.front())) {
    distance += adj_matrix(path.back(), path.front());
  } else {
    ResetPath(path.front());
  }
}

std::vector<std::pair<int, double>>
s21::AntColonyAlgorithms::Ant::CalculateProbabilities(
    int current_vertex, const Matrix<int>& adj_matrix,
    const Matrix<double>& pheromones) {
  std::vector<std::pair<int, double>> probabilities;
  double sum_product = 0.0;

  int num_vertices = static_cast<int>(adj_matrix.cols());
  for (int next_vertex = 0; next_vertex < num_vertices; next_vertex++) {
    if (!adj_matrix(current_vertex, next_vertex) || IsVisited(next_vertex))
      continue;

    double pheromone = pheromones(current_vertex, next_vertex);
    double path_weight = adj_matrix(current_vertex, next_vertex);
    double product = pheromone * path_weight;

    probabilities.emplace_back(next_vertex, product);
    sum_product += product;
  }

  for (auto& p : probabilities) {
    p.second /= sum_product;
  }

  return probabilities;
}

void s21::AntColonyAlgorithms::Ant::NormalizeProbabilities(
    std::vector<std::pair<int, double>>& probabilities) {
  double sum_product = 0.0;
  for (const auto& p : probabilities) {
    sum_product += p.second;
  }

  for (auto& p : probabilities) {
    p.second /= sum_product;
  }
}

void s21::AntColonyAlgorithms::Ant::ResetPath(int start_vertex) {
  path.clear();
  path.push_back(start_vertex);
  distance = 0;
}

bool s21::AntColonyAlgorithms::Ant::IsVisited(int vertex) const {
  return std::find(path.begin(), path.end(), vertex) != path.end();
}

int s21::AntColonyAlgorithms::Ant::ChooseNextVertex(
    const std::vector<std::pair<int, double>>& probabilities) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  double random_value = dis(gen);
  double cumulative_probability = 0.0;

  for (const auto& p : probabilities) {
    cumulative_probability += p.second;
    if (random_value <= cumulative_probability) {
      return p.first;
    }
  }

  return -1;
}
}  // namespace s21