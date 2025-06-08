#include "../../minishell.h"

static void	skip_quotes(char *str, int *i)
{
	if (str[*i] && str[*i] == '"')
			{
				(*i)++;
				while (str[*i] && str[*i] != '"')
					(*i)++;
			}
			if (str[*i] && str[*i] == '\'')
			{
				(*i)++;
				while (str[*i] && str[*i] != '\'')
					(*i)++;
			}
}

static void	count_operators(char *str, int *i, int *words)
{
	(*words)++;
	(*i)++;
	if (str[*i] == '<' || str[*i] == '>')
		(*i)++;
}

// Returns the number of arguments in the input string.
size_t	count_args(char *input)
{
	int		i;
	bool	w_flag;
	int		words;

	i = 0;
	words = 0;
	w_flag = false;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		while (input[i] && input[i] != ' ' && !ft_isoperator(input[i]))
		{
			w_flag = true;
			skip_quotes(input, &i);
			if (input[i] && input[i] != ' ')
				i++;
		}
		if (w_flag)
			words++;
		w_flag = false;
		if (ft_isoperator(input[i]))
			count_operators(input, &i, &words);
	}
	return(words);
}