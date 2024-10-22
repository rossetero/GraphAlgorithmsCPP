#include "tests.h"

TEST(Graph, TestLoad_1) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm1.txt");
  EXPECT_EQ(g.adjacency_matrix().rows(), 5);
}

TEST(Graph, TestLoad_2) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm2.txt");
  EXPECT_EQ(g.adjacency_matrix().rows(), 4);
}

TEST(Graph, TestLoad_3) {
  s21::Graph g;
  EXPECT_THROW(g.LoadGraphFromFile("./tests/test_matrices/tm404.txt"),
               std::runtime_error);
}

TEST(Graph, TestExport_1) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm2.txt");
  g.ExportGraphToDot("./tests/dot_outputs/dot_tm2.txt");
  std::fstream f("./tests/dot_outputs/dot_tm2.txt");
  std::string s;
  f >> s;
  f.close();
  EXPECT_EQ(s, "digraph");
}

TEST(Graph, TestExport_2) {
  s21::Graph g;
  g.LoadGraphFromFile("./tests/test_matrices/tm1.txt");
  g.ExportGraphToDot("./tests/dot_outputs/dot_tm1.txt");
  std::fstream f("./tests/dot_outputs/dot_tm1.txt");
  std::string s;
  f >> s;
  f.close();
  EXPECT_EQ(s, "graph");
}
