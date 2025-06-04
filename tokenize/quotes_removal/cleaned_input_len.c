#include "../../minishell.h"

char	*find_env_var(char *input)
{

}

static bool	through_doublequotes(char *input, int *i, int *l)
{
	(*i)++;
	while(input[*i] && input[*i] !='"')
	{
		// if (input[*i] == '$')
		// 	find_env_var();
		(*l)++;
		(*i)++;
	}
	if (!input[*i])
	{
		ft_printfd(2, RED"Double quotes unclosed.\n"NO_ALL);
		return (false);
	}
	(*i)++;
	return (true);
}

static bool	through_singlequotes(char *input, int *i, int *l)
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
		return (false);
	}
	(*i)++;
	return (true);
}

// Returns the string's lenght whitout outer quotes or -1 if said quotes are 
//  not closed.
int	ft_clean_input_len(char *input)
{
	int		i;
	int	l;

	i = 0;
	l = 0;
	while(input[i])
	{
		if (input[i] =='"')
		{
			if (!through_doublequotes(input, &i, &l))
				return (-1);
		}
		if (input[i] == '\'')
		{
			if (!through_singlequotes(input, &i, &l))
				return (-1);
		}
		if (!input[i])
			return (l);
		i++;
		l++;
	}
	return (l);
}
