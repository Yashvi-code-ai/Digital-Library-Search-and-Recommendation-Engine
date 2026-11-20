CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Iinclude
SOURCES = src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/greedy.c src/dp.c src/backtracking.c
CORE_SOURCES = src/searching.c src/sorting.c src/greedy.c src/dp.c src/backtracking.c
TARGET = digital_library
TEST = test_core
LIBRARY_TEST = test_library

.PHONY: all run test clean
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

$(TEST): tests/test_core.c $(CORE_SOURCES)
	$(CC) $(CFLAGS) tests/test_core.c $(CORE_SOURCES) -o $(TEST)

$(LIBRARY_TEST): tests/test_library.c src/book.c src/library.c
	$(CC) $(CFLAGS) tests/test_library.c src/book.c src/library.c -o $(LIBRARY_TEST)

run: $(TARGET)
	./$(TARGET)

test: $(TEST) $(LIBRARY_TEST)
	./$(TEST)
	./$(LIBRARY_TEST)

clean:
	rm -f $(TARGET) $(TARGET).exe $(TEST) $(TEST).exe $(LIBRARY_TEST) $(LIBRARY_TEST).exe
