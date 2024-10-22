CXX = g++
CXXFLAGS = -O2 -Wall -Werror -Wextra -std=c++17
GCOVFLAGS = --coverage

GRAPH_SRC = ./graph/graph.cc
GRAPH_OBJS = $(GRAPH_SRC:.cc=.o)

ALG_SRC = ./graph/graph_algorithms.cc \
		  ./graph/ant_colony_algorithms.cc

ALG_OBJS = $(ALG_SRC:.cc=.o)

HELPER_SRC = $(wildcard stack_queue/**/*.cc)
HELPER_OBJS = $(HELPER_SRC:.cc=.o)

TESTS_SRC = $(wildcard tests/*.cc)
TESTS_OBJS = $(TESTS_SRC:.cc=.o)
TESTS_LIBS = -lgtest

LIBS = -lncurses

EXEC = console.out

all : clean s21_graph s21_graph_algorithms console

gcov_report: clean
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) $(GRAPH_SRC) $(ALG_SRC) $(HELPER_SRC) $(TESTS_SRC) -o gcov_test $(TESTS_LIBS)
	./gcov_test
	lcov --capture --directory . --output-file coverage.info --rc geninfo_unexecuted_blocks=1 --ignore-errors gcov,source,mismatch,inconsistent
	lcov --extract coverage.info "*/graph/*.cc" --output-file coverage_filtered.info
	genhtml -o report/ coverage_filtered.info
	rm -rf *.gcno *.gcov *.gcda *.info *.a tests/*.o
	open ./report/index.html

test: s21_graph s21_graph_algorithms $(TESTS_OBJS)
	$(CXX) $(CXXFLAGS) $(TESTS_OBJS) s21_graph_algorithms.a s21_graph.a -o unit_test $(TESTS_LIBS)
	./unit_test

s21_graph: $(GRAPH_OBJS)
	ar rcs s21_graph.a $(GRAPH_OBJS)

s21_graph_algorithms: $(ALG_OBJS) $(HELPER_OBJS)
	ar rcs s21_graph_algorithms.a $(ALG_OBJS) $(HELPER_OBJS)

console: s21_graph_algorithms s21_graph
	$(CXX) console.cc $(CXXFLAGS) s21_graph.a s21_graph_algorithms.a -o $(EXEC) $(LIBS)

./stack_queue/**/%.o: ./stack_queue/**/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

./graph/%.o: ./graph/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

./tests/%.o: ./tests/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clang:
	find . -iname *.h -o -iname *.tpp -o -iname *.c -o -iname *.cpp | xargs clang-format -n -style=Google

clangi:
	find . -iname *.h -o -iname *.tpp -o -iname *.c -o -iname *.cpp | xargs clang-format -i -style=Google

clean:
	rm -f ./graph/*.o
	rm -f ./tests/*.o
	rm -f ./stack_queue/**/*.o
	rm -f s21_graph.a unit_test gcov_test s21_graph_algorithms.a
	rm -f ./tests/dot_outputs/dot*.txt
	rm -rf report
	rm -f *.out
	rm -f *.gcda *.gcno
