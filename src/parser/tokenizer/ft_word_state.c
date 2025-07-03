#include "word_state.h"

// Forward declarations for functions in ft_handle_word.c
char	*ft_handle_quotes_in_word(t_shell *shell, const char *input, size_t *i,
		char *result);
char	*ft_expand_variable(t_shell *shell, const char *input, size_t *i);
char	*ft_append_to_result(t_shell *shell, char *result, const char *append);
char	*ft_process_regular_text(t_shell *shell, const char *input, size_t *i);

char	*ft_process_word_part(t_word_state *state)
{
	char	*temp;

	if (state->input[*state->i] == '"' || state->input[*state->i] == '\'')
	{
		*state->was_quoted = 1;
		state->result = ft_handle_quotes_in_word(state->shell, state->input,
				state->i, state->result);
	}
	else if (state->input[*state->i] == '$')
	{
		temp = ft_expand_variable(state->shell, state->input, state->i);
		state->result = ft_append_to_result(state->shell, state->result, temp);
		ft_track_free(state->shell, temp);
	}
	else
	{
		temp = ft_process_regular_text(state->shell, state->input, state->i);
		state->result = ft_append_to_result(state->shell, state->result, temp);
		ft_track_free(state->shell, temp);
	}
	return (state->result);
}

