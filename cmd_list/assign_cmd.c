#include "../minishell.h"

// Returns the number of TOKEN_WORDs before the next pipe or the end of input.
static size_t	count_w_tokens(t_token **tokens, int *i)
{
	int		j;
	size_t	count;

	j = *i;
	count = 0;
	while (tokens[j] && tokens[j]->type != TOKEN_PIPE)
	{
		if (tokens[j]->type == TOKEN_WORD)
			count++;
		j++;
	}
	return (count);
}

// Concatenates TOKEN_WORDs not separated by a pipe in a single command array.
char	**assign_cmd_value(t_token **tokens, int *i)
{
	char	**cmd;
	size_t	n_word_tokens;
	size_t	j;

	j = 0;
	n_word_tokens = count_w_tokens(tokens, i);
	cmd = ft_calloc(n_word_tokens + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (j < n_word_tokens)
	{
		if (tokens[*i]->type == TOKEN_WORD)
			cmd[j++] = tokens[*i]->value;
		(*i)++;
	}
	return (cmd);
}
