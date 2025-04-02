# Makefile

# The name of the final executable
NAME = libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes

# Directories
SRCDIR = src
OBJDIR = obj

# Source and object files
SRC = ft_bzero.c \
      ft_isalnum.c \
      ft_isalpha.c \
      ft_isascii.c \
      ft_isdigit.c \
      ft_isprint.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_memset.c \
      ft_memchr.c \
      ft_memcmp.c \
      ft_strchr.c \
      ft_strnstr.c \
      ft_strlcat.c \
      ft_strlcpy.c \
      ft_strlen.c \
      ft_strncmp.c \
      ft_strrchr.c \
      ft_tolower.c \
      ft_toupper.c \
      ft_atoi.c \
      ft_calloc.c \
      ft_strdup.c \
      ft_substr.c \
      ft_strjoin.c \
      ft_strtrim.c \
      ft_split.c \
      ft_itoa.c \
      ft_itoa_unsigned.c \
      ft_itoa_hex.c \
	  ft_lstnew.c \
	  ft_lstadd_front.c \
	  ft_lstadd_back.c \
	  ft_lstdelone.c \
	  ft_lstsize.c \
	  ft_lstlast.c \
      ft_strmapi.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
      ft_printf.c \
      format_one.c \
      format_two.c

# Add the source directory prefix to source files
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

# Generate object file names in the object directory
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#  Prevents make from confusing these targets with files of the same name.
.PHONY: all clean fclean re

# Default rule
all: $(NAME)

# Rule to build static library
$(NAME): $(OBJS)
	ar rcs $@ $^

# Ensure the object directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule for compiling source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for cleaning up object files
clean:
	rm -f $(OBJS)

# Rule for full clean (removes executable as well)
fclean: clean
	rm -f $(NAME)

# Rule for re-making the project from scratch
re: fclean all

# To prevent unnecessary relinks, we make sure that the `all` target
# does not force a rebuild of the $(NAME) if the object files have not changed.
# This is implicit in the way make works by checking the timestamps of prerequisites.
