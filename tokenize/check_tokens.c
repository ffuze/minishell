#include "../minishell.h"

// Checks whether the tokenized strngs are acceptable and/or 
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
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_PIPE \
			&& tokens[i + 1] && tokens[i + 1]->type == TOKEN_PIPE)
		{
			ft_printfd(2, \
				RED"norminette: syntax error near token `%s'\n" \
				NO_ALL, tokens[i]->value);
			return (false);
		}
		else if (tokens[i]->type == TOKEN_PIPE && (!tokens[i + 1] || i == 0))
		{
			ft_printfd(2, \
				RED"norminette: syntax error near token `%s'\n" \
				NO_ALL, tokens[i]->value);
			return (false);
		}
		i++;
	}
	return (true);
}
