NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = src/main.c src/utils/memory.c
OBJ = $(SRC:.c=.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
TEST_SRC = tests/unit/test_memory.c tests/unity/unity.c src/utils/memory.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_BINARY = test

all: $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Linking minishell..."
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "Minishell built successfully!"

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

build-test: $(LIBFT) $(TEST_OBJ)
	@echo "Linking test binary..."
	@$(CC) $(TEST_OBJ) -L$(LIBFT_DIR) -lft -o $(TEST_BINARY)
	@echo "Test binary built successfully!"

run-test: build-test
	@echo "========== Running Tests =========="
	@./$(TEST_BINARY)
	@echo "========== Tests Complete ========="

test: run-test

tests/unit/%.o: tests/unit/%.c minishell.h
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

tests/unity/%.o: tests/unity/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ) $(TEST_OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning binaries..."
	@rm -f $(NAME) $(TEST_BINARY)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
