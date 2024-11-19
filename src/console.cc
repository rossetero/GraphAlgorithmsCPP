#include <ncurses.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "graph/graph.h"
#include "graph/graph_algorithms.h"

namespace s21 {

class ConsoleInterface {
 public:
  ConsoleInterface() : isGraphLoaded(false) {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
  }

  ~ConsoleInterface() { endwin(); }

  void Run() {
    int choice;
    while (true) {
      clear();
      printMenu();
      choice = getch();
      switch (choice) {
        case '1':
          loadGraphFromFile();
          break;
        case '2':
          if (isGraphLoaded)
            breadthFirstSearch();
          else
            showGraphNotLoadedMessage();
          break;
        case '3':
          if (isGraphLoaded)
            depthFirstSearch();
          else
            showGraphNotLoadedMessage();
          break;
        case '4':
          if (isGraphLoaded)
            shortestPathBetweenVertices();
          else
            showGraphNotLoadedMessage();
          break;
        case '5':
          if (isGraphLoaded)
            shortestPathsBetweenAllVertices();
          else
            showGraphNotLoadedMessage();
          break;
        case '6':
          if (isGraphLoaded)
            leastSpanningTree();
          else
            showGraphNotLoadedMessage();
          break;
        case '7':
          if (isGraphLoaded)
            solveTravelingSalesmanProblem();
          else
            showGraphNotLoadedMessage();
          break;
        case '8':
          if (isGraphLoaded)
            fordBellman();
          else
            showGraphNotLoadedMessage();
          break;
        case '9':
          exportGraph();
          break;
        case '0':
          return;
        default:
          break;
      }
    }
  }

 private:
  Graph graph;
  bool isGraphLoaded;

  void printMenu() {
    mvprintw(0, 0, "Graph Algorithms Menu");
    mvprintw(2, 0, "1. Load graph from file");
    mvprintw(3, 0, "2. Breadth-First Search");
    mvprintw(4, 0, "3. Depth-First Search");
    mvprintw(5, 0, "4. Shortest path between two vertices");
    mvprintw(6, 0, "5. Shortest paths between all vertices");
    mvprintw(7, 0, "6. Least spanning tree");
    mvprintw(8, 0, "7. Solve Traveling Salesman Problem");
    mvprintw(9, 0, "8. Ford-Bellman Alogrithm");
    mvprintw(10, 0, "9. Export graph to .dot file");
    mvprintw(11, 0, "0. Exit");
    mvprintw(13, 0, "Enter your choice: ");
    refresh();
  }

  void fordBellman() {
    clear();
    mvprintw(0, 0, "Enter start vertex: ");
    refresh();
    try {
      int startVertex = -1;
      scanw((char*)"%d", &startVertex);
      std::vector<int> result =
          GraphAlgorithms::FordBellmanAlgorithm(graph, startVertex);
      mvprintw(2, 0, "Ford-Bellman Result:");
      for (size_t i = 0; i < result.size(); i++) {
        int vertex = result[i];
        mvprintw(4 + i, 0, "%d ", vertex);
      }
    } catch (...) {
      mvprintw(2, 0, "Search Error!");
    }
    refresh();
    getch();
  }

  void loadGraphFromFile() {
    clear();
    mvprintw(0, 0, "Enter file path: ");
    refresh();
    char filePath[256];
    getstr(filePath);
    std::ifstream file(filePath);
    if (!file.is_open()) {
      mvprintw(2, 0, "Error: Could not open file.");
      refresh();
      getch();
      return;
    }
    try {
      graph.LoadGraphFromFile(filePath);
      isGraphLoaded = true;
      mvprintw(2, 0, "Graph loaded successfully.");
    } catch (...) {
      mvprintw(2, 0, "Graph loading error.");
    }
    refresh();
    getch();
  }

  void exportGraph() {
    clear();
    mvprintw(0, 0, "Enter file path: ");
    refresh();
    char filePath[256];
    getstr(filePath);
    try {
      graph.ExportGraphToDot(filePath);
      isGraphLoaded = true;
      mvprintw(2, 0, "Graph exported successfully.");
    } catch (...) {
      mvprintw(2, 0, "Graph loading error.");
    }
    refresh();
    getch();
  }

  void breadthFirstSearch() {
    clear();
    mvprintw(0, 0, "Enter start vertex: ");
    refresh();
    try {
      int startVertex = -1;
      scanw((char*)"%d", &startVertex);
      std::vector<int> result =
          GraphAlgorithms::BreadthFirstSearch(graph, startVertex);
      mvprintw(2, 0, "Breadth-First Search Result:");
      for (size_t i = 0; i < result.size(); i++) {
        int vertex = result[i];
        mvprintw(4 + i, 0, "%d ", vertex);
      }
    } catch (...) {
      mvprintw(2, 0, "Breadth-First Search Error!");
    }
    refresh();
    getch();
  }

  void depthFirstSearch() {
    clear();
    mvprintw(0, 0, "Enter start vertex: ");
    refresh();
    try {
      int startVertex = -1;
      scanw((char*)"%d", &startVertex);
      std::vector<int> result =
          GraphAlgorithms::DepthFirstSearch(graph, startVertex);
      mvprintw(2, 0, "Depth-First Search Result:");
      for (size_t i = 0; i < result.size(); i++) {
        int vertex = result[i];
        mvprintw(4 + i, 0, "%d ", vertex);
      }
    } catch (...) {
      mvprintw(2, 0, "Depth-First Search Error!");
    }
    refresh();
    getch();
  }

  void shortestPathBetweenVertices() {
    clear();
    mvprintw(0, 0, "Enter start vertex: ");
    refresh();
    try {
      int startVertex = -1;
      scanw((char*)"%d", &startVertex);
      mvprintw(2, 0, "Enter end vertex: ");
      refresh();
      int endVertex = -1;
      scanw((char*)"%d", &endVertex);
      int result = GraphAlgorithms::GetShortestPathBetweenVertices(
          graph, startVertex, endVertex);
      mvprintw(4, 0, "Shortest path: %d", result);
    } catch (...) {
      mvprintw(2, 0, "Shortest path Error!");
    }
    refresh();
    getch();
  }

  void shortestPathsBetweenAllVertices() {
    clear();
    try {
      Matrix<int> result =
          GraphAlgorithms::GetShortestPathsBetweenAllVertices(graph);
      mvprintw(0, 0, "Shortest paths between all vertices:");
      for (size_t i = 0; i < result.rows(); i++) {
        for (size_t j = 0; j < result.cols(); j++) {
          mvprintw(2 + i, 4 * j, "%d ", result(i, j));
        }
      }
    } catch (...) {
      mvprintw(2, 0, "Shortest path not found!");
    }
    refresh();
    getch();
  }

  void leastSpanningTree() {
    clear();
    try {
      Matrix<int> result = GraphAlgorithms::GetLeastSpanningTree(graph);
      mvprintw(0, 0, "Least spanning tree:");
      for (size_t i = 0; i < result.rows(); i++) {
        for (size_t j = 0; j < result.cols(); j++) {
          mvprintw(2 + i, 4 * j, "%d ", result(i, j));
        }
      }
    } catch (...) {
      mvprintw(2, 0, "Least spanning tree error!");
    }
    refresh();
    getch();
  }

  void solveTravelingSalesmanProblem() {
    clear();
    try {
      GraphAlgorithms::TsmResult result =
          GraphAlgorithms::SolveTravelingSalesmanProblem(graph);
      mvprintw(0, 0, "Traveling Salesman Problem Result:");
      mvprintw(2, 0, "Route: ");

      for (size_t i = 0; i < result.vertices.size(); i++) {
        int vertex = result.vertices[i];

        mvprintw(4, 0 + i * 2, "%d ", vertex);
      }
      mvprintw(6, 0, "Distance: %f", result.distance);
    } catch (...) {
      mvprintw(6, 0, "Traveling Salesman Problem error!");
    }
    refresh();
    getch();
  }

  void showGraphNotLoadedMessage() {
    clear();
    mvprintw(0, 0, "Error: Graph is not loaded.");
    refresh();
    getch();
  }
};

}  // namespace s21

int main() {
  s21::ConsoleInterface interface;
  interface.Run();
  return 0;
}
