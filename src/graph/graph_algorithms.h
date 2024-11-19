#ifndef _GRAPH_ALGORITHMS_H_
#define _GRAPH_ALGORITHMS_H_

#include <limits>
#include <vector>

#include "../stack_queue/queue/queue.h"
#include "../stack_queue/stack/stack.h"
#include "ant_colony_algorithms.h"
#include "graph.h"
#include "t_matrix.h"

namespace s21 {
class GraphAlgorithms {
 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

  static std::vector<int> FordBellmanAlgorithm(const Graph& graph,
                                               int start_vertex);
  static std::vector<int> DepthFirstSearch(const Graph& graph,
                                           int start_vertex);

  static std::vector<int> BreadthFirstSearch(const Graph& graph,
                                             int start_vertex);

  static int GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                            int vertex2);

  static Matrix<int> GetShortestPathsBetweenAllVertices(Graph& graph);

  static Matrix<int> GetLeastSpanningTree(Graph& graph);

  static TsmResult SolveTravelingSalesmanProblem(Graph& graph);

 private:
  static int DijkstraMinWeightAlgorithm(Graph& graph, int startVertex,
                                        int endVertex);
  static Matrix<int> FloydsAlgorithm(Graph& graph);
};

}  // namespace s21

#endif