NAME = minishell

# Directories
SRC_DIR = src
INIT_DIR = $(SRC_DIR)/init
PARSER_DIR = $(SRC_DIR)/parser
TOKENIZER_DIR = $(PARSER_DIR)/tokenizer
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
		$(TOKENIZER_DIR)/ft_handle_multichar_op.c \
		$(TOKENIZER_DIR)/ft_handle_operator.c \
		$(TOKENIZER_DIR)/ft_handle_paren.c \
		$(TOKENIZER_DIR)/ft_handle_quotes.c \
		$(TOKENIZER_DIR)/ft_handle_dollar.c \
		$(TOKENIZER_DIR)/ft_expand_variables.c \
		$(TOKENIZER_DIR)/ft_handle_word.c \
		$(TOKENIZER_DIR)/ft_process_char.c \
		$(TOKENIZER_DIR)/ft_skip_whitespace.c \
		$(TOKENIZER_DIR)/ft_tokenize_loop.c \
		$(TOKENIZER_DIR)/ft_tokenize.c

OBJS =	$(SRCS:%.c=$(OBJ_DIR)/%.o)

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

# Test rule to trigger test Makefile and run tests
test:
	@echo "Building and running tests..."
	$(MAKE) -C $(TEST_DIR) test

valgrind-test:
	@echo "Running tests with Valgrind..."
	$(MAKE) -C $(TEST_DIR) valgrind-test

# Debug
debug:
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"

# Cleaning
clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean

fclean: clean
	@echo "Cleaning binaries..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(TEST_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test valgrind-test debug