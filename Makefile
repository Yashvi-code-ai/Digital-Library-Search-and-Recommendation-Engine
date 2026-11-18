CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Iinclude
TARGET = digital_library
TEST_LIBRARY = test_library
TEST_ALGORITHMS = test_search_sort
TEST_DIVIDE_CONQUER = test_divide_conquer
TEST_GREEDY = test_greedy
TEST_DP = test_dp
SOURCES = src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c

.PHONY: all run test clean
all: $(TARGET)

$(TARGET): $(SOURCES) include/book.h include/library.h include/algorithms.h include/divide_conquer.h include/greedy.h include/dp.h
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

test: $(TEST_LIBRARY) $(TEST_ALGORITHMS) $(TEST_DIVIDE_CONQUER) $(TEST_GREEDY) $(TEST_DP)
	./$(TEST_LIBRARY)
	./$(TEST_ALGORITHMS)
	./$(TEST_DIVIDE_CONQUER)
	./$(TEST_GREEDY)
	./$(TEST_DP)

clean:
	rm -f $(TARGET) $(TARGET).exe $(TEST_LIBRARY) $(TEST_LIBRARY).exe $(TEST_ALGORITHMS) $(TEST_ALGORITHMS).exe $(TEST_DIVIDE_CONQUER) $(TEST_DIVIDE_CONQUER).exe $(TEST_GREEDY) $(TEST_GREEDY).exe $(TEST_DP) $(TEST_DP).exe tests/test_books_tmp.csv
