NAME = vec2bin
CC = epiclang
CFLAGS = -Wall -Wextra -Iinclude -g3
LDFLAGS = -lm

SRCS_DIR = src
SRCS = \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/parse_vec.c \
	$(SRCS_DIR)/write_cvec.c \
	$(SRCS_DIR)/buffers.c

BUILD_DIR = build
OBJS_DIR = $(BUILD_DIR)/obj
DEPS_DIR = $(BUILD_DIR)/dep
BIN_DIR = $(BUILD_DIR)/bin
TARGET = $(BIN_DIR)/$(NAME)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEPS = $(SRCS:$(SRCS_DIR)/%.c=$(DEPS_DIR)/%.d)

all: $(NAME)

$(NAME): $(TARGET)
	ln -sf $(TARGET) $(NAME)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c include/*.h
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
