NAME = minishell

# Directories
SRC_DIR = src
INIT_DIR = $(SRC_DIR)/init
PARSER_DIR = $(SRC_DIR)/parser
TOKENIZER_DIR = $(PARSER_DIR)/tokenizer
EXECUTION_DIR = $(SRC_DIR)/execution
EXEC_DIR = $(EXECUTION_DIR)/exec
PROC_DIR = $(EXECUTION_DIR)/proc
UTILS_DIR = $(SRC_DIR)/utils
INC_DIR = includes
OBJ_DIR = obj
LIBFT_DIR = libft
TEST_DIR = tests

# Source files
SRCS =	$(INIT_DIR)/main.c \
		$(INIT_DIR)/minishell_loop.c \
		$(UTILS_DIR)/memory.c \
		$(TOKENIZER_DIR)/ft_add_token.c \
		$(TOKENIZER_DIR)/ft_create_token.c \
		$(TOKENIZER_DIR)/ft_finalize_tokens.c \
		$(TOKENIZER_DIR)/ft_free_tokens.c \
		$(TOKENIZER_DIR)/ft_handle_operator.c \
		$(TOKENIZER_DIR)/ft_handle_quotes.c \
		$(TOKENIZER_DIR)/ft_handle_word.c \
		$(TOKENIZER_DIR)/ft_process_char.c \
		$(TOKENIZER_DIR)/ft_skip_whitespace.c \
		$(TOKENIZER_DIR)/ft_tokenize_loop.c \
		$(TOKENIZER_DIR)/ft_tokenize.c \
		$(EXEC_DIR)/ft_exec_command.c \
		$(EXEC_DIR)/ft_exec_path.c \
		$(PROC_DIR)/ft_proc_line.c

OBJS =	$(SRCS:%.c=$(OBJ_DIR)/%.o)

#TEST_SRC = $(TEST_DIR)/unit/test_memory.c \
        	$(TEST_DIR)/unity/unity.c \
        	$(UTILS_DIR)/memory.c
TEST_SRC =	$(TEST_DIR)/unit/test_exec_line.c \
    		$(TEST_DIR)/unity/unity.c \
        	$(UTILS_DIR)/memory.c \
			$(UTILS_DIR)/command.c \
			$(INIT_DIR)/minishell_loop.c \
		   	$(TOKENIZER_DIR)/ft_add_token.c \
			$(TOKENIZER_DIR)/ft_create_token.c \
			$(TOKENIZER_DIR)/ft_finalize_tokens.c \
			$(TOKENIZER_DIR)/ft_free_tokens.c \
			$(TOKENIZER_DIR)/ft_handle_operator.c \
			$(TOKENIZER_DIR)/ft_handle_quotes.c \
			$(TOKENIZER_DIR)/ft_handle_word.c \
			$(TOKENIZER_DIR)/ft_process_char.c \
			$(TOKENIZER_DIR)/ft_skip_whitespace.c \
			$(TOKENIZER_DIR)/ft_tokenize_loop.c \
			$(TOKENIZER_DIR)/ft_tokenize.c \
			$(EXEC_DIR)/ft_exec_command.c \
			$(EXEC_DIR)/ft_exec_path.c \
			$(PROC_DIR)/ft_proc_line.c \
			$(PROC_DIR)/ft_proc_word.c \
			$(PROC_DIR)/ft_proc_redir_in.c


TEST_OBJS = $(TEST_SRC:%.c=$(OBJ_DIR)/%.o)
TEST_BINARY = test_binary

# Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

# Rules
all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJS)
	@echo "Linking minishell..."
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Minishell built successfully!"

$(LIBFT_DIR)/libft.a:
	@echo "Building libft..."
	$(MAKE) -C $(LIBFT_DIR)

# Pattern rules
$(OBJ_DIR)/%.o: %.c $(INC_DIR)/minishell.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Test binary
$(TEST_BINARY): $(LIBFT_DIR)/libft.a $(TEST_OBJS)
	@echo "Linking test binary..."
	$(CC) $(TEST_OBJS) $(LDFLAGS) -o $(TEST_BINARY)
	@echo "Test binary built successfully!"

test: $(TEST_BINARY)
	@echo "========== Running Tests =========="
	./$(TEST_BINARY)
	@echo "========== Tests Complete ========="

valgrind-test: $(TEST_BINARY)
	@echo "========== Running Tests with Valgrind =========="
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./readline.supp ./$(TEST_BINARY)
	@echo "========== Valgrind Tests Complete ========="

#debug
debug:
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"

# Cleaning
clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning binaries..."
	rm -f $(NAME) $(TEST_BINARY)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test valgrind-test