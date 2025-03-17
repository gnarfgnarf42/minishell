NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= src/main.c \
		  src/utils/memory.c
OBJS	= $(SRCS:.c=.o)
LIBFT	= libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
