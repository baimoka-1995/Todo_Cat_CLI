CC = gcc

CFLAGS = -Wall -Wextra -g \
	-Isrc/core \
	-Isrc/cmd \
	-Isrc/storage \
	-Isrc/cat

TARGET = todo
OBJ_DIR = build

SRCS = \
	src/main.c \
	src/core/list.c \
	src/core/search.c \
	src/storage/storage.c \
	src/cmd/cmd.c \
	src/cat/cat.c \
	src/cat/cat_assets.c

OBJS = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 通用编译规则
$(OBJ_DIR)/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean