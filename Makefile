# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Iinclude

# Directories and files
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests
EXAMPLE_DIR = example

# Targets
TARGET = libutils.a
TEST_EXECUTABLE = test
LINKED_LIST_TEST_EXECUTABLE = test_linked_list

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Test source files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Build library
all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Run all tests
check: $(TARGET)
	$(CC) $(CFLAGS) -o $(TEST_EXECUTABLE) $(TEST_SRCS) -L. -lutils
	./$(TEST_EXECUTABLE)

# Run linked list example test
test_linked_list: $(TARGET)
	$(CC) $(CFLAGS) -o $(LINKED_LIST_TEST_EXECUTABLE) \
		$(EXAMPLE_DIR)/linked_list.c -L. -lutils
	./$(LINKED_LIST_TEST_EXECUTABLE)

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_EXECUTABLE) $(LINKED_LIST_TEST_EXECUTABLE)

.PHONY: all clean check test_linked_list
