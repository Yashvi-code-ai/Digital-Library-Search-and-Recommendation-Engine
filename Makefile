CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -Iinclude
TARGET = digital_library
SOURCES = src/main.c src/book.c src/library.c

.PHONY: all run clean
all: $(TARGET)

$(TARGET): $(SOURCES) include/book.h include/library.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
