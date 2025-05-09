# Test Makefile
TEST_BINARY = test_binary

# Directories
SRC_DIR = ../src
UTILS_DIR = $(SRC_DIR)/utils
INC_DIR = ../includes
OBJ_DIR = ../obj
LIBFT_DIR = ../libft
TEST_DIR = .

# Source files
TEST_SRC = $(TEST_DIR)/unit/test_memory.c \
           $(TEST_DIR)/unity/unity.c \
           $(UTILS_DIR)/memory.c

TEST_OBJS = $(TEST_SRC:%.c=$(OBJ_DIR)/%.o)

# Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

# Rules
all: $(TEST_BINARY)

$(TEST_BINARY): $(LIBFT_DIR)/libft.a $(TEST_OBJS)
	@echo "Linking test binary..."
	$(CC) $(TEST_OBJS) $(LDFLAGS) -o $(TEST_BINARY)
	@echo "Test binary built successfully!"

$(LIBFT_DIR)/libft.a:
	@echo "Building libft..."
	$(MAKE) -C $(LIBFT_DIR)

# Pattern rules
$(OBJ_DIR)/%.o: %.c $(INC_DIR)/minishell.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Run tests
test: $(TEST_BINARY)
	@echo "========== Running Tests =========="
	./$(TEST_BINARY)
	@echo "========== Tests Complete ========="

valgrind-test: $(TEST_BINARY)
	@echo "========== Running Tests with Valgrind =========="
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=../readline.supp ./$(TEST_BINARY)
	@echo "========== Valgrind Tests Complete ========="

# Cleaning
clean:
	@echo "Cleaning test object files..."
	rm -f $(TEST_OBJS)

fclean: clean
	@echo "Cleaning test binary..."
	rm -f $(TEST_BINARY)

re: fclean all

.PHONY: all clean fclean re test valgrind-test
