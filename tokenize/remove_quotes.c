#include "../minishell.h"

/* static void	skip_quotes(char *str, int *i)
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

static size_t	count_input_words(char *input)
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
} */
//-----------------------------------------------------------------------------

static int	through_doublequotes(char *input, int *i, size_t *l)
{
	(*i)++;
	while(input[*i] && input[*i] !='"')
	{
		(*l)++;
		(*i)++;
	}
	if (!input[*i])
	{
		ft_printfd(2, RED"Double quotes unclosed.\n"NO_ALL);
		return (0);
	}
	(*i)++;
	return (1);
}

static int	through_singlequotes(char *input, int *i, size_t *l)
{
	(*i)++;
	while(input[*i] && input[*i] !='\'')
	{
		(*l)++;
		(*i)++;
	}
	if (!input[*i])
	{
		ft_printfd(2, RED"Single quotes unclosed.\n"NO_ALL);
		return (0);
	}
	(*i)++;
	return (1);
}

size_t	ft_clean_input_len(char *input)
{
	int		i;
	size_t	l;

	i = 0;
	l = 0;
	while(input[i])
	{
		if (input[i] =='"')
		{
			if (!through_doublequotes(input, &i, &l))
				return (0);//-1?
		}
		if (input[i] == '\'')
		{
			if (!through_singlequotes(input, &i, &l))
				return (0);//-1?
		}
		if (!input[i])
			return (l);
		i++;
		l++;
	}
	return (l);
}

// // Returns the string input without quotes (except those between a pair of
// // quotes of a different type).
// // An error message is diplayed if outer quotes are unclosed.
// char	*ft_remove_quotes(char *input)// Gestire qui l'espansione delle variabili
// {
// 	// printf(MAGENTA"N parole = %zu\n"NO_ALL, count_input_words(input));
// 	// printf(MAGENTA"Len input pulito = %zu\n"NO_ALL, ft_clean_input_len(input));
// 	// return (NULL);
// 	char	*clean_input;
// 	int		i;
// 	int		j;
// 	bool	quote;

// 	i = 0;
// 	j = 0;
// 	quote = false;
// 	if (!input[0])
// 		return (NULL);
// 	// clean_input = ft_calloc(count_input_words(input), sizeof(char **));
// 	clean_input = ft_calloc(ft_clean_input_len(input), sizeof(char *));
// }
