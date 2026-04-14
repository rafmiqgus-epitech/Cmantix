NAME = cmantix_tests
CC = clang
CFLAGS = -Wall -Wextra -I../include -g3
CRITERION_FLAGS = -lcriterion -lm -lncurses

TEST_SRCS = \
	test_cvec.c \
	test_hash.c \
	test_cosine.c \
	test_score.c \
	test_game.c \
	test_history.c

PROJECT_SRCS = $(shell find ../src -name '*.c' ! -name 'main.c' | sort)

all: $(NAME)

$(NAME): $(TEST_SRCS) $(PROJECT_SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(TEST_SRCS) $(PROJECT_SRCS) $(CRITERION_FLAGS)

run: $(NAME)
	./$(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all run clean fclean re
