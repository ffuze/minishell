#include "../../minishell.h"

/* static bool	environment_variable_check(t_msh *msh, int c)
{
	if (msh->env_var_flag == false && c != '$')
		return (false);
	else
		return (true);
} */

static void	through_doublequotes(/* t_msh *msh,  */char *input, int *i, int *l)
{
	(*i)++;
	(*l)++;
	while(input[*i] && input[*i] !='"')
	{
		// msh->env_var_flag = environment_variable_check(msh, input[*i]);
		// (*l)++;
		(*i)++;
	}
	if (!input[*i])
	{
		ft_printfd(2, RED"Double quotes unclosed.\n"NO_ALL);
		*l = -1;
		return ;
	}
	(*i)++;
	return ;
}

static void	through_singlequotes(char *input, int *i, int *l)
{
	(*i)++;
	(*l)++;
	while(input[*i] && input[*i] !='\'')
	{
		// (*l)++;
		(*i)++;
	}
	if (!input[*i])
	{
		ft_printfd(2, RED"Single quotes unclosed.\n"NO_ALL);
		*l = -1;
		return ;
	}
	(*i)++;
	return ;
}

// Checks whether there are variables to expand or unclosed quotes.
int	ft_parse_input(t_msh *msh, char *input)
{
	int		i;
	int		l;

	i = 0;
	l = 0;
	msh->env_var_flag = false;/////////////////////////////////
	while(l >= 0 && input[i])
	{
		if (l >= 0 && input[i] =='"')
			through_doublequotes(/* msh,  */input, &i, &l);
		if (l >= 0 && input[i] == '\'')
			through_singlequotes(input, &i, &l);
		if (l >= 0 && input[i] && input[i] !='"' && input[i] !='\'')
			{
				// msh->env_var_flag = environment_variable_check(msh, input[i]);
				i++;
				l++;
			}
	}
	return (l);
}
