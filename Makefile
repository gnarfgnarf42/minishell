NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
SRCS        = src/main.c \
              src/parser/parser.c \
              src/executor/executor.c \
              ...
OBJS        = $(SRCS:.c=.o)
LIBFT       = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft            # build libft first
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
