CC = gcc
CFLAGS = -Wall -Werror -Iinclude

TARGET = libutils.a
TEST_EXECUTABLE = test

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

test: $(TARGET)
	$(CC) $(CFLAGS) -o $(TEST_EXECUTABLE) $(TEST_DIR)/test_linked_list.c -L. -lutils
	./$(TEST_EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_EXECUTABLE)

.PHONY: all clean
