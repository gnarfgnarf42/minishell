NAME = minishell

# Directories
SRC_DIR = 	src
INIT_DIR = 	$(SRC_DIR)/init
PARSER_DIR = $(SRC_DIR)/parser
TOKENIZER_DIR =	$(PARSER_DIR)/tokenizer
EXECUTION_DIR = $(SRC_DIR)/execution
EXEC_DIR = $(EXECUTION_DIR)/exec
PROC_DIR = $(EXECUTION_DIR)/proc
CMD_DIR = $(EXECUTION_DIR)/cmd
UTILS_DIR = $(SRC_DIR)/utils
INC_DIR = includes
OBJ_DIR = obj
LIBFT_DIR = libft
TEST_DIR = tests

# Source files
SRCS =		$(INIT_DIR)/main.c \
			$(INIT_DIR)/minishell_loop.c \
			$(UTILS_DIR)/memory_basic.c \
			$(UTILS_DIR)/memory_string.c \
			$(UTILS_DIR)/command.c \
			$(UTILS_DIR)/env.c \
			$(UTILS_DIR)/error.c \
			$(UTILS_DIR)/fd.c \
			$(UTILS_DIR)/builtin.c \
			$(UTILS_DIR)/path.c \
			$(UTILS_DIR)/tokens.c \
			$(TOKENIZER_DIR)/ft_add_token.c \
			$(TOKENIZER_DIR)/ft_create_token.c \
			$(TOKENIZER_DIR)/ft_expand_variables.c \
			$(TOKENIZER_DIR)/ft_finalize_tokens.c \
			$(TOKENIZER_DIR)/ft_free_tokens.c \
			$(TOKENIZER_DIR)/ft_handle_dollar.c \
			$(TOKENIZER_DIR)/ft_handle_multichar_op.c \
			$(TOKENIZER_DIR)/ft_handle_operator.c \
			$(TOKENIZER_DIR)/ft_handle_paren.c \
			$(TOKENIZER_DIR)/ft_handle_quotes.c \
			$(TOKENIZER_DIR)/ft_handle_word.c \
			$(TOKENIZER_DIR)/ft_handle_word_quotes.c \
			$(TOKENIZER_DIR)/ft_handle_word_process.c \
			$(TOKENIZER_DIR)/ft_process_char.c \
			$(TOKENIZER_DIR)/ft_skip_whitespace.c \
			$(TOKENIZER_DIR)/ft_tokenize_loop.c \
			$(TOKENIZER_DIR)/ft_tokenize.c \
			$(EXEC_DIR)/ft_exec_command.c \
			$(EXEC_DIR)/ft_exec_path.c \
			$(EXEC_DIR)/ft_exec_shell.c \
			$(PROC_DIR)/ft_proc_tokens.c \
			$(PROC_DIR)/ft_proc_word.c \
			$(PROC_DIR)/ft_proc_redir_in.c \
			$(PROC_DIR)/ft_proc_redir_out.c \
			$(PROC_DIR)/ft_proc_append.c \
			$(PROC_DIR)/ft_proc_heredoc.c \
			$(PROC_DIR)/ft_proc_pipe.c \
			$(CMD_DIR)/ft_ms_cd.c \
			$(CMD_DIR)/ft_ms_echo.c \
			$(CMD_DIR)/ft_ms_env.c \
			$(CMD_DIR)/ft_ms_exit.c \
			$(CMD_DIR)/ft_ms_export.c \
			$(CMD_DIR)/ft_ms_pwd.c \
			$(CMD_DIR)/ft_ms_unset.c 

OBJS =		$(SRCS:%.c=$(OBJ_DIR)/%.o)

TEST_SRC =	$(TEST_DIR)/unit/test_envp.c \
    		$(TEST_DIR)/unity/unity.c \
			$(INIT_DIR)/minishell_loop.c \
        	$(UTILS_DIR)/memory_basic.c \
			$(UTILS_DIR)/memory_string.c \
			$(UTILS_DIR)/command.c \
			$(UTILS_DIR)/env.c \
			$(UTILS_DIR)/error.c \
			$(UTILS_DIR)/fd.c \
			$(UTILS_DIR)/builtin.c \
			$(UTILS_DIR)/path.c \
			$(UTILS_DIR)/tokens.c \
			$(TOKENIZER_DIR)/ft_add_token.c \
			$(TOKENIZER_DIR)/ft_create_token.c \
			$(TOKENIZER_DIR)/ft_expand_variables.c \
			$(TOKENIZER_DIR)/ft_finalize_tokens.c \
			$(TOKENIZER_DIR)/ft_free_tokens.c \
			$(TOKENIZER_DIR)/ft_handle_dollar.c \
			$(TOKENIZER_DIR)/ft_handle_operator.c \
			$(TOKENIZER_DIR)/ft_handle_paren.c \
			$(TOKENIZER_DIR)/ft_handle_quotes.c \
			$(TOKENIZER_DIR)/ft_handle_word.c \
			$(TOKENIZER_DIR)/ft_handle_word_quotes.c \
			$(TOKENIZER_DIR)/ft_handle_word_process.c \ \
			$(TOKENIZER_DIR)/ft_merge_adjacent_words.c \
			$(TOKENIZER_DIR)/ft_process_char.c \
			$(TOKENIZER_DIR)/ft_skip_whitespace.c \
			$(TOKENIZER_DIR)/ft_tokenize_loop.c \
			$(TOKENIZER_DIR)/ft_tokenize.c \
			$(EXEC_DIR)/ft_exec_command.c \
			$(EXEC_DIR)/ft_exec_path.c \
			$(EXEC_DIR)/ft_exec_shell.c \
			$(PROC_DIR)/ft_proc_tokens.c \
			$(PROC_DIR)/ft_proc_word.c \
			$(PROC_DIR)/ft_proc_redir_in.c \
			$(PROC_DIR)/ft_proc_redir_out.c \
			$(PROC_DIR)/ft_proc_append.c \
			$(PROC_DIR)/ft_proc_heredoc.c \
			$(PROC_DIR)/ft_proc_pipe.c \
			$(CMD_DIR)/ft_ms_cd.c \
			$(CMD_DIR)/ft_ms_echo.c \
			$(CMD_DIR)/ft_ms_env.c \
			$(CMD_DIR)/ft_ms_exit.c \
			$(CMD_DIR)/ft_ms_export.c \
			$(CMD_DIR)/ft_ms_pwd.c \
			$(CMD_DIR)/ft_ms_unset.c 

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