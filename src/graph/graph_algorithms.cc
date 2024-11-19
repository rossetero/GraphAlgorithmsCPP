#include "graph_algorithms.h"

namespace s21 {

std::vector<int> GraphAlgorithms::FordBellmanAlgorithm(const Graph& graph,
                                                       int start_vertex) {
  const Matrix<int>& adjacency_matrix = graph.adjacency_matrix();
  int order = graph.order();
  const int inf = std::numeric_limits<int>::max();
  std::vector<int> distance(order, inf);
  distance[start_vertex] = 0;
  for (int i = 0; i < order - 1; ++i) {
    for (int u = 0; u < order; ++u) {
      for (int v = 0; v < order; ++v) {
        if (adjacency_matrix(u, v) != 0 && distance[u] != inf &&
            distance[u] + adjacency_matrix(u, v) < distance[v]) {
          distance[v] = distance[u] + adjacency_matrix(u, v);
        }
      }
    }
  }
  return distance;
}

std::vector<int> GraphAlgorithms::DepthFirstSearch(const Graph& graph,
                                                   int start_vertex) {
  if (start_vertex < 0 || static_cast<size_t>(start_vertex) >= graph.order()) {
    throw std::runtime_error("No such vertex.");
  }
  const Matrix<int>& adjacency_matrix = graph.adjacency_matrix();
  std::vector<bool> is_visited(adjacency_matrix.rows(), false);
  Stack stack{start_vertex};
  std::vector<int> result;

  while (!stack.Empty()) {
    int vertex = stack.Top();
    stack.Pop();

    if (is_visited[vertex]) {
      continue;
    }

    result.push_back(vertex);
    is_visited[vertex] = true;

    for (size_t i = 0; i < adjacency_matrix.rows(); i++) {
      if (adjacency_matrix(vertex, i) && !is_visited[i]) {
        stack.Push(i);
      }
    }
  }

  return result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(const Graph& graph,
                                                     int start_vertex) {
  if (start_vertex < 0 || static_cast<size_t>(start_vertex) >= graph.order()) {
    throw std::runtime_error("No such vertex.");
  }
  const Matrix<int>& adjacency_matrix = graph.adjacency_matrix();
  std::vector<bool> is_visited(adjacency_matrix.rows(), false);
  Queue queue{start_vertex};
  std::vector<int> result;

  while (!queue.Empty()) {
    int vertex = queue.Front();
    queue.Pop();

    if (is_visited[vertex]) {
      continue;
    }

    result.push_back(vertex);
    is_visited[vertex] = true;

    for (size_t i = 0; i < adjacency_matrix.rows(); i++) {
      if (adjacency_matrix(vertex, i) && !is_visited[i]) {
        queue.Push(i);
      }
    }
  }

  return result;
}

int GraphAlgorithms::DijkstraMinWeightAlgorithm(Graph& graph, int start_vertex,
                                                int end_vertex) {
  if (start_vertex < 0 || static_cast<size_t>(end_vertex) >= graph.order()) {
    throw std::runtime_error("Invalid input");
  }

  const Matrix<int>& adjacency_matrix = graph.adjacency_matrix();
  int order = graph.order();

  std::vector<int> cost(order, std::numeric_limits<int>::max());
  std::vector<int> path(order, -1);
  std::vector<bool> is_visited(order, false);

  is_visited[start_vertex] = true;
  cost[start_vertex] = 0;
  int current_vertex = start_vertex;

  while (!is_visited[end_vertex]) {
    for (int neighbor_vertex = 0; neighbor_vertex < order; ++neighbor_vertex) {
      int edge_weight = adjacency_matrix(current_vertex, neighbor_vertex);

      if (edge_weight && !is_visited[neighbor_vertex]) {
        int new_cost = edge_weight + cost[current_vertex];
        if (new_cost < cost[neighbor_vertex]) {
          cost[neighbor_vertex] = new_cost;
          path[neighbor_vertex] = current_vertex;
        }
      }
    }

    is_visited[current_vertex] = true;
    bool is_deadlock = true;

    int min_cost = std::numeric_limits<int>::max();
    for (int i = 0; i < order; ++i) {
      if (!is_visited[i] && cost[i] < min_cost) {
        min_cost = cost[i];
        current_vertex = i;
        is_deadlock = false;
      }
    }

    if (is_deadlock && !is_visited[end_vertex]) {
      throw std::runtime_error("No Path");
    }
  }

  return cost[end_vertex];
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                                    int vertex2) {
  return DijkstraMinWeightAlgorithm(graph, vertex1, vertex2);
}

Matrix<int> GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) {
  return FloydsAlgorithm(graph);
}

Matrix<int> GraphAlgorithms::FloydsAlgorithm(Graph& graph) {
  const int inf = std::numeric_limits<int>::max();
  const Matrix<int>& adjacency_matrix = graph.adjacency_matrix();
  size_t order = graph.order();
  Matrix<int> dist(order, order);
  for (size_t i = 0; i < order; i++) {
    for (size_t j = 0; j < order; j++) {
      if (i == j) {
        dist(i, j) = 0;
      } else {
        dist(i, j) = inf;
      }
      if (adjacency_matrix(i, j) != 0) {
        dist(i, j) = adjacency_matrix(i, j);
      }
    }
  }

  for (size_t v = 0; v < order; v++) {
    for (size_t a = 0; a < order; a++) {
      for (size_t b = 0; b < order; b++) {
        if (dist(a, v) != inf && dist(v, b) != inf &&
            dist(a, b) > dist(a, v) + dist(v, b)) {
          dist(a, b) = dist(a, v) + dist(v, b);
        }
      }
    }
  }

  return dist;
}

Matrix<int> GraphAlgorithms::GetLeastSpanningTree(Graph& graph) {
  const int inf = std::numeric_limits<int>::max();
  const Matrix<int>& adjacency_matrix = graph.adjacency_matrix();
  size_t order = graph.order();
  Matrix<int> mst_matrix(order, order);
  std::vector<bool> selected(order, false);
  selected[0] = true;

  for (size_t edge_number = 0; edge_number < order - 1; edge_number++) {
    int min = inf;
    int x = 0;
    int y = 0;

    for (size_t i = 0; i < order; i++) {
      if (selected[i]) {
        for (size_t j = 0; j < order; j++) {
          if (!selected[j] && adjacency_matrix(i, j)) {
            if (min > adjacency_matrix(i, j)) {
              min = adjacency_matrix(i, j);
              x = i;
              y = j;
            }
          }
        }
      }
    }
    mst_matrix(x, y) = adjacency_matrix(x, y);
    mst_matrix(y, x) = adjacency_matrix(x, y);
    selected[y] = true;
  }

  return mst_matrix;
}

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph& graph) {
  s21::AntColonyAlgorithms::TsmResult result =
      AntColonyAlgorithms::SolveTravelingSalesmanProblem(graph, 75, 2);
  if (result.distance == 0) {
    throw std::runtime_error("No path. ");
  }

  return GraphAlgorithms::TsmResult{std::move(result.vertices),
                                    std::move(result.distance)};
}

}