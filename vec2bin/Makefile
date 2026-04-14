NAME = vec2bin
CC = clang
CFLAGS = -Wall -Wextra -g3
LDFLAGS = -lm

SRCS = \
	main.c \
	parse_vec.c \
	write_cvec.c \
	buffers.c

BUILD_DIR = build
OBJS_DIR = $(BUILD_DIR)/obj
DEPS_DIR = $(BUILD_DIR)/dep
BIN_DIR = $(BUILD_DIR)/bin
TARGET = $(BIN_DIR)/$(NAME)
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPS = $(SRCS:%.c=$(DEPS_DIR)/%.d)

all: $(NAME)

$(NAME): $(TARGET)
	ln -sf $(TARGET) $(NAME)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJS_DIR)/%.o: %.c vec2bin.h
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEPS_DIR)/$*.d)
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEPS_DIR)/$*.d -MT $@ -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
