CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Iinclude
TARGET = digital_library
SOURCES = src/main.c src/book.c src/library.c
TEST_TARGET = test_library

.PHONY: all run test clean
all: $(TARGET)

$(TARGET): $(SOURCES) include/book.h include/library.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TEST_TARGET): tests/test_library.c src/book.c src/library.c include/book.h include/library.h
	$(CC) $(CFLAGS) tests/test_library.c src/book.c src/library.c -o $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe $(TEST_TARGET) $(TEST_TARGET).exe tests/test_books_tmp.csv
