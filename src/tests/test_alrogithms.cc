#include "tests.h"

TEST(DFS, tm1) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm1.txt");
  std::vector<int> v = s21::GraphAlgorithms::DepthFirstSearch(g, 4);
  std::vector<int> exp{4, 3, 0, 1, 2};
  EXPECT_EQ(exp, v);
}

TEST(DFS, tm2) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm2.txt");
  std::vector<int> v = s21::GraphAlgorithms::DepthFirstSearch(g, 0);
  std::vector<int> exp{0, 1, 3, 2};
  EXPECT_EQ(exp, v);
}

TEST(DFS, tm3) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm3.txt");
  std::vector<int> v = s21::GraphAlgorithms::DepthFirstSearch(g, 0);
  std::vector<int> exp{0, 2, 3, 4, 1};
  EXPECT_EQ(exp, v);
}


TEST(BFS, tm1) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm1.txt");
  std::vector<int> v = s21::GraphAlgorithms::BreadthFirstSearch(g, 4);
  std::vector<int> exp{4, 1, 2, 3, 0};
  EXPECT_EQ(exp, v);
}

TEST(BFS, tm2) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm2.txt");
  std::vector<int> v = s21::GraphAlgorithms::BreadthFirstSearch(g, 0);
  std::vector<int> exp{0, 1, 2, 3};
  EXPECT_EQ(exp, v);
}

TEST(BFS, tm3) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm3.txt");
  std::vector<int> v = s21::GraphAlgorithms::BreadthFirstSearch(g, 0);
  std::vector<int> exp{0, 1, 2, 3, 4};
  EXPECT_EQ(exp, v);
}

TEST(DFS, tm4) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm4.txt");
  std::vector<int> v = s21::GraphAlgorithms::DepthFirstSearch(g, 0);
  std::vector<int> exp{0, 4, 3, 2, 1};
  EXPECT_EQ(exp, v);
}

TEST(BFS, tm4_1) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm4.txt");
  std::vector<int> v = s21::GraphAlgorithms::BreadthFirstSearch(g, 0);
  std::vector<int> exp{0, 1, 2, 4, 3};
  EXPECT_EQ(exp, v);
}

TEST(Floyd, tm1) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm1.txt");
  s21::Matrix<int> m =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(g);
  std::vector<int> exp{0, 2, 5, 6, 7, 2, 0, 3, 6, 5, 5, 3, 0,
                       5, 4, 6, 6, 5, 0, 1, 7, 5, 4, 1, 0};
  EXPECT_EQ(m.EqVector(exp), true);
  // m.print();
}

TEST(Floyd, tm2) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm2.txt");
  s21::Matrix<int> m =
      s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(g);
  std::vector<int> exp{0, 5, 3, 8, -5, 0, -2, 3, -3, 2, 0, 5, -8, -3, -5, 0};
  EXPECT_EQ(m.EqVector(exp), true);
  // m.print();
}

TEST(MST, tm1) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm1.txt");
  s21::Matrix<int> m = s21::GraphAlgorithms::GetLeastSpanningTree(g);
  std::vector<int> exp{0, 2, 0, 0, 0, 2, 0, 3, 0, 0, 0, 3, 0,
                       0, 4, 0, 0, 0, 0, 1, 0, 0, 4, 1, 0};
  EXPECT_EQ(m.EqVector(exp), true);
}

TEST(MST, tm3) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm3.txt");
  s21::Matrix<int> m = s21::GraphAlgorithms::GetLeastSpanningTree(g);
  std::vector<int> exp{0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0,
                       0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0};
  EXPECT_EQ(m.EqVector(exp), true);
}

TEST(MST, tm3_1) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm4.txt");
  EXPECT_ANY_THROW(s21::GraphAlgorithms::TsmResult res = s21::GraphAlgorithms::SolveTravelingSalesmanProblem(g));
}

TEST(MST, tm5) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm5.txt");
  int res = s21::GraphAlgorithms::GetShortestPathBetweenVertices(g, 3, 0);
  EXPECT_EQ(res, 16);
}

TEST(MST, tm6) {
  s21::Graph g;
  EXPECT_ANY_THROW(g.LoadGraphFromFile("./tests/test_matrices/tm6.txt"));
}


TEST(MST, tm7) {
  s21::Graph g;
  EXPECT_ANY_THROW(g.LoadGraphFromFile("./tests/test_matrices/tm7.txt"));
}

TEST(MST, tm8) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm8.txt");
  s21::GraphAlgorithms::TsmResult res = s21::GraphAlgorithms::SolveTravelingSalesmanProblem(g);
  EXPECT_EQ(res.distance, 58);
}
