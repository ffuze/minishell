#include "../minishell.h"

static bool	check_pipe_tokens(t_token **tokens, int *i)
{
	if (tokens[*i]->type == TOKEN_PIPE \
			&& tokens[(*i) + 1] && tokens[(*i) + 1]->type == TOKEN_PIPE)
		{
			ft_printfd(2, \
				RED"norminette: syntax error near token `%s'\n" \
				NO_ALL, tokens[*i]->value);
			return (false);
		}
	else if (tokens[*i]->type == TOKEN_PIPE && \
					(!tokens[(*i) + 1] || *i == 0))
	{
		ft_printfd(2, \
			RED"norminette: syntax error near token `%s'\n" \
			NO_ALL, tokens[*i]->value);
		return (false);
	}
	return (true);
}

static bool	search_word_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] && tokens[i]->type != TOKEN_WORD)
		i++;
	if (tokens[i] && tokens[i]->type == TOKEN_WORD)
		return (true);
	else
		return (false);
}

// Checks whether the tokenized strings are acceptable and/or 
//  are associated to the needed token.
bool	check_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	if (!tokens[0])
		return (false);
	else if (ft_strcmp(tokens[0]->value, ".") == 0)
	{
		ft_printfd(2, \
			RED"norminette: syntax error near token `%s'\n" \
			NO_ALL, tokens[i]->value);
		return (false);
	}
	if (!search_word_tokens(tokens))
		return (false);
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_PIPE)
		{
			if (!check_pipe_tokens(tokens, &i))
				return (false);
		}
		i++;
	}
	return (true);
}
