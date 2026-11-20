CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Iinclude
SOURCES = src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c src/backtracking.c src/flow_matching.c src/string_number_theory.c src/analysis.c
CORE_SOURCES = src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c src/backtracking.c src/flow_matching.c src/string_number_theory.c src/analysis.c
TARGET = digital_library
TEST = test_core

.PHONY: all run test clean
all: $(TARGET)
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)
$(TEST): tests/test_core.c $(CORE_SOURCES)
	$(CC) $(CFLAGS) tests/test_core.c $(CORE_SOURCES) -o $(TEST)
run: $(TARGET)
	./$(TARGET)
test: $(TEST)
	./$(TEST)
clean:
	rm -f $(TARGET) $(TARGET).exe $(TEST) $(TEST).exe
