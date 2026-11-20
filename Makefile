CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Iinclude
SOURCES = src/main.c src/book.c src/library.c src/searching.c src/sorting.c src/divide_conquer.c src/greedy.c src/dp.c src/backtracking.c src/flow_matching.c src/string_number_theory.c src/analysis.c
TARGET = digital_library

.PHONY: all run clean
all: $(TARGET)
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)
run: $(TARGET)
	./$(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe
