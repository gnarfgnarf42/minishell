# Test Makefile for Minishell AST

NAME = test_runner

# Directories
TEST_DIR = .
UNIT_DIR = $(TEST_DIR)/unit
INTEGRATION_DIR = $(TEST_DIR)/integration
SRC_DIR = ../src
INC_DIR = ../includes
LIBFT_DIR = ../libft
OBJ_DIR = obj

# Source files
TEST_SRCS = run_tests.c \
			test_framework.c \
			$(UNIT_DIR)/test_ast_creation.c \
			$(UNIT_DIR)/test_ast_parsing.c \
			$(UNIT_DIR)/test_ast_pipeline.c \
			$(UNIT_DIR)/test_ast_execution.c \
			$(UNIT_DIR)/test_ast_edge_cases.c \
			$(INTEGRATION_DIR)/test_ast_integration.c

# Minishell source files needed for testing
MINISHELL_SRCS = $(SRC_DIR)/parser/ft_ast.c \
				$(SRC_DIR)/parser/ft_parse_ast.c \
				$(SRC_DIR)/parser/ft_parse_pipeline.c \
				$(SRC_DIR)/parser/ft_parse_tokens.c \
				$(SRC_DIR)/execution/ft_exec_ast.c \
				$(SRC_DIR)/execution/ft_exec_ast_utils.c \
				$(SRC_DIR)/execution/ft_exec_ast_pipe.c \
				$(SRC_DIR)/utils/memory_basic.c \
				$(SRC_DIR)/utils/memory_string.c \
				$(SRC_DIR)/utils/command.c \
				$(SRC_DIR)/utils/env.c \
				$(SRC_DIR)/utils/error.c \
				$(SRC_DIR)/utils/fd.c \
				$(SRC_DIR)/utils/builtin.c \
				$(SRC_DIR)/utils/path.c \
				$(SRC_DIR)/parser/tokenizer/ft_tokenize.c \
				$(SRC_DIR)/parser/tokenizer/ft_create_token.c \
				$(SRC_DIR)/parser/tokenizer/ft_add_token.c \
				$(SRC_DIR)/parser/tokenizer/ft_finalize_tokens.c \
				$(SRC_DIR)/parser/tokenizer/ft_free_tokens.c \
				$(SRC_DIR)/parser/tokenizer/ft_handle_dollar.c \
				$(SRC_DIR)/parser/tokenizer/ft_handle_multichar_op.c \
				$(SRC_DIR)/parser/tokenizer/ft_handle_operator.c \
				$(SRC_DIR)/parser/tokenizer/ft_handle_paren.c \
				$(SRC_DIR)/parser/tokenizer/ft_handle_quotes.c \
				$(SRC_DIR)/parser/tokenizer/ft_handle_word.c \
				$(SRC_DIR)/parser/tokenizer/ft_handle_word_quotes.c \
				$(SRC_DIR)/parser/tokenizer/ft_handle_word_process.c \
				$(SRC_DIR)/parser/tokenizer/ft_process_char.c \
				$(SRC_DIR)/parser/tokenizer/ft_skip_whitespace.c \
				$(SRC_DIR)/parser/tokenizer/ft_tokenize_loop.c \
				$(SRC_DIR)/parser/tokenizer/ft_expand_variables.c \
				$(SRC_DIR)/execution/exec/ft_exec_command.c \
				$(SRC_DIR)/execution/exec/ft_exec_path.c \
				$(SRC_DIR)/execution/cmd/ft_ms_cd.c \
				$(SRC_DIR)/execution/cmd/ft_ms_echo.c \
				$(SRC_DIR)/execution/cmd/ft_ms_env.c \
				$(SRC_DIR)/execution/cmd/ft_ms_exit.c \
				$(SRC_DIR)/execution/cmd/ft_ms_export.c \
				$(SRC_DIR)/execution/cmd/ft_ms_pwd.c \
				$(SRC_DIR)/execution/cmd/ft_ms_unset.c

ALL_SRCS = $(TEST_SRCS) $(MINISHELL_SRCS)
OBJS = $(ALL_SRCS:%.c=$(OBJ_DIR)/%.o)

# Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR) -I$(TEST_DIR) -g
LDFLAGS = -L$(LIBFT_DIR) -lft

# Rules
all: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJS)
	@echo "Linking test runner..."
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Test runner built successfully!"

$(LIBFT_DIR)/libft.a:
	@echo "Building libft..."
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Test targets
test: $(NAME)
	@echo "Running all tests..."
	./$(NAME)

test-creation: $(NAME)
	@echo "Running AST creation tests..."
	./$(NAME) creation

test-parsing: $(NAME)
	@echo "Running AST parsing tests..."
	./$(NAME) parsing

test-pipeline: $(NAME)
	@echo "Running AST pipeline tests..."
	./$(NAME) pipeline

test-execution: $(NAME)
	@echo "Running AST execution tests..."
	./$(NAME) execution

test-edge: $(NAME)
	@echo "Running AST edge case tests..."
	./$(NAME) edge

test-integration: $(NAME)
	@echo "Running AST integration tests..."
	./$(NAME) integration

# Cleaning
clean:
	@echo "Cleaning test objects..."
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Cleaning test binaries..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all test test-creation test-parsing test-pipeline test-execution test-edge test-integration clean fclean re