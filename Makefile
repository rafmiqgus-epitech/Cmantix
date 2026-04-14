NAME = cmantix
CC = epiclang
CFLAGS = -Wall -Wextra -Iinclude -g3
LDFLAGS = -lncurses -lm

SRCS_DIR = src
SRCS = \
	$(SRCS_DIR)/main.c \
	$(SRCS_DIR)/cvec/cvec_load.c \
	$(SRCS_DIR)/cvec/cvec_header.c \
	$(SRCS_DIR)/cvec/cvec_free.c \
	$(SRCS_DIR)/hash/hash_table.c \
	$(SRCS_DIR)/hash/hash_utils.c \
	$(SRCS_DIR)/similarity/cosine.c \
	$(SRCS_DIR)/similarity/score.c \
	$(SRCS_DIR)/game/game_init.c \
	$(SRCS_DIR)/game/game_loop.c \
	$(SRCS_DIR)/game/game_guess.c \
	$(SRCS_DIR)/game/game_history.c \
	$(SRCS_DIR)/game/game_secret.c \
	$(SRCS_DIR)/ui/ui_init.c \
	$(SRCS_DIR)/ui/ui_draw.c \
	$(SRCS_DIR)/ui/ui_input.c \
	$(SRCS_DIR)/ui/ui_colors.c \
	$(SRCS_DIR)/ui/ui_progress.c \
	$(SRCS_DIR)/parsing/args.c

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

tests_run: all
	$(MAKE) -C tests re
	./tests/$(NAME)_tests

compdb:
	@mkdir -p $(BUILD_DIR)
	bear --output $(BUILD_DIR)/compile_commands.json -- $(MAKE) -B $(OBJS)

recompdb: fclean compdb all

-include $(DEPS)

.PHONY: all clean fclean re tests_run compdb recompdb
