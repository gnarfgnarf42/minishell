NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
SRC         = src/main.c src/utils/memory.c
OBJ         = $(SRC:.c=.o)
LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

TEST_SRC    = tests/unit/test_memory.c tests/unity/unity.c src/utils/memory.c
TEST_OBJ    = $(TEST_SRC:.c=.o)
TEST_BINARY = test_binary

.PHONY: all clean fclean re test

# Default target
all: $(NAME)

# Build libft if not already built
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Build minishell
$(NAME): $(LIBFT) $(OBJ)
	@echo "Linking minishell..."
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "Minishell built successfully!"

# Compile object files for minishell
%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# ---- TEST BINARY ----

# This is the *real file* target that builds the "test" binary.
$(TEST_BINARY): $(LIBFT) $(TEST_OBJ)
	@echo "Linking test binary..."
	@$(CC) $(TEST_OBJ) -L$(LIBFT_DIR) -lft -o $(TEST_BINARY)
	@echo "Test binary built successfully!"

# Single phony "test" target to build and run tests
test: $(TEST_BINARY)
	@echo "========== Running Tests =========="
	@./$(TEST_BINARY)
	@echo "========== Tests Complete ========="

# Pattern rules for test source files
tests/unit/%.o: tests/unit/%.c minishell.h
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

tests/unity/%.o: tests/unity/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# ---- CLEANING ----

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ) $(TEST_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning binaries..."
	@rm -f $(NAME) $(TEST_BINARY)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
