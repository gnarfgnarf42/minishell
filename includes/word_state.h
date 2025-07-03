#ifndef WORD_STATE_H
# define WORD_STATE_H

# include "parser.h"

typedef struct s_word_state
{
	char	*result;
	int		*was_quoted;
	size_t	*i;
	t_shell	*shell;
	const char	*input;
}				t_word_state;

char	*ft_process_word_part(t_word_state *state);

#endif
