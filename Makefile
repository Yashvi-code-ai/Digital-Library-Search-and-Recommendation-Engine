CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Iinclude
TARGET = digital_library
TEST_LIBRARY = test_library
TEST_ALGORITHMS = test_search_sort
TEST_DIVIDE_CONQUER = test_divide_conquer
TEST_GREEDY = test_greedy
TEST_DP = test_dp
TEST_BACKTRACKING = test_backtracking
TEST_FLOW = test_flow_matching
TEST_PHASE8 = test_string_number_theory
TEST_PHASE9 = test_analysis
SOURCES = src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c src/backtracking.c src/flow_matching.c src/string_number_theory.c src/analysis.c

.PHONY: all run test clean
all: $(TARGET)

$(TARGET): $(SOURCES) include/book.h include/library.h include/algorithms.h include/divide_conquer.h include/greedy.h include/dp.h include/backtracking.h include/flow_matching.h include/string_number_theory.h include/analysis.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TEST_LIBRARY): tests/test_library.c src/book.c src/library.c include/book.h include/library.h
	$(CC) $(CFLAGS) tests/test_library.c src/book.c src/library.c -o $(TEST_LIBRARY)

$(TEST_ALGORITHMS): tests/test_search_sort.c src/searching.c src/sorting.c include/book.h include/algorithms.h
	$(CC) $(CFLAGS) tests/test_search_sort.c src/searching.c src/sorting.c -o $(TEST_ALGORITHMS)

$(TEST_DIVIDE_CONQUER): tests/test_divide_conquer.c src/divide_conquer.c include/divide_conquer.h
	$(CC) $(CFLAGS) tests/test_divide_conquer.c src/divide_conquer.c -o $(TEST_DIVIDE_CONQUER)

$(TEST_GREEDY): tests/test_greedy.c src/greedy.c include/greedy.h
	$(CC) $(CFLAGS) tests/test_greedy.c src/greedy.c -o $(TEST_GREEDY)

$(TEST_DP): tests/test_dp.c src/dp.c include/dp.h
	$(CC) $(CFLAGS) tests/test_dp.c src/dp.c -o $(TEST_DP)

$(TEST_BACKTRACKING): tests/test_backtracking.c src/backtracking.c include/backtracking.h
	$(CC) $(CFLAGS) tests/test_backtracking.c src/backtracking.c -o $(TEST_BACKTRACKING)

$(TEST_FLOW): tests/test_flow_matching.c src/flow_matching.c include/flow_matching.h
	$(CC) $(CFLAGS) tests/test_flow_matching.c src/flow_matching.c -o $(TEST_FLOW)

$(TEST_PHASE8): tests/test_string_number_theory.c src/string_number_theory.c include/string_number_theory.h
	$(CC) $(CFLAGS) tests/test_string_number_theory.c src/string_number_theory.c -o $(TEST_PHASE8)

$(TEST_PHASE9): tests/test_analysis.c src/analysis.c include/analysis.h
	$(CC) $(CFLAGS) tests/test_analysis.c src/analysis.c -o $(TEST_PHASE9)

test: $(TEST_LIBRARY) $(TEST_ALGORITHMS) $(TEST_DIVIDE_CONQUER) $(TEST_GREEDY) $(TEST_DP) $(TEST_BACKTRACKING) $(TEST_FLOW) $(TEST_PHASE8) $(TEST_PHASE9)
	./$(TEST_LIBRARY)
	./$(TEST_ALGORITHMS)
	./$(TEST_DIVIDE_CONQUER)
	./$(TEST_GREEDY)
	./$(TEST_DP)
	./$(TEST_BACKTRACKING)
	./$(TEST_FLOW)
	./$(TEST_PHASE8)
	./$(TEST_PHASE9)

clean:
	rm -f $(TARGET) $(TARGET).exe $(TEST_LIBRARY) $(TEST_LIBRARY).exe $(TEST_ALGORITHMS) $(TEST_ALGORITHMS).exe $(TEST_DIVIDE_CONQUER) $(TEST_DIVIDE_CONQUER).exe $(TEST_GREEDY) $(TEST_GREEDY).exe $(TEST_DP) $(TEST_DP).exe $(TEST_BACKTRACKING) $(TEST_BACKTRACKING).exe $(TEST_FLOW) $(TEST_FLOW).exe $(TEST_PHASE8) $(TEST_PHASE8).exe $(TEST_PHASE9) $(TEST_PHASE9).exe tests/test_books_tmp.csv
