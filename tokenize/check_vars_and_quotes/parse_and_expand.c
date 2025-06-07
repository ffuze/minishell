#include "../../minishell.h"

// Searches the var in the environment and returns its value.
static char	*find_value(char **envp, char *input, size_t *i)
{
	char	*var_name;
	size_t	start;
	size_t	j;
	size_t	name_l;

	j = 0;
	(*i)++;
	start = *i;
	while(input[*i] && ((input[*i] > '0' && input[*i] < '9') || \
						(input[*i] > 'A' && input[*i] < 'Z') || \
						(input[*i] > 'a' && input[*i] < 'z')))
		(*i)++;
	var_name = ft_substr(input, start, (*i - start));
	if(!var_name)
		return (NULL);
	name_l = ft_strlen(var_name);
	while (envp[j])
	{
		if (ft_strncmp(envp[j], var_name, name_l) == 0)
			return (free(var_name), ft_strchr2(envp[j], '='));
		j++;
	}
	return (free(var_name), "");
}

static size_t	through_doublequotes(t_msh *msh, char *input, size_t *i)
{
	size_t	j;

	j = ft_strlen(msh->exp_input);
	msh->exp_input[j++] = input[(*i)++];
	// (*i)++;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			msh->exp_input = ft_strjoin2(msh->exp_input, find_value(msh->envp2, input, i));
			if (!msh->exp_input)
				return (0);
			j = ft_strlen(msh->exp_input);
			msh->exp_input = ft_realloc(msh->exp_input, j, j + ft_strlen(input) - *i);
			// (*i)++;
		}
		// ft_printf(GREEN"input[i] = %c, j = %d \n"NO_ALL, input[*i], j);/////////////////////////
		if (input[*i] && input[*i] != '$' && input[*i] != '"')
			msh->exp_input[j++] = input[(*i)++];
	}
	// if (input[*i])
	// 	(*i)++;
	return (j);
}

static void	through_singlequotes(t_msh *msh, char *input, size_t *i, size_t *j)
{
	// (*i)++;
	msh->exp_input[(*j)++] = input[(*i)++];
	while (input[*i] && input[*i] != '\'')
		msh->exp_input[(*j)++] = input [(*i)++];
	// if (input[*i])
	// 	(*i)++;
}

// Returns the string "input" without outer quotes.
char	*ft_expandedcpy(t_msh *msh, char *input)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		ft_printf(BLUE"input[i] = %d\n"NO_ALL, input[i]);/////////////////////////////////////
		if (input[i] == '"')
			j = through_doublequotes(msh, input, &i);
		ft_printf(GREEN"input[i] = %c, j = %d \n"NO_ALL, input[i], j);///////////////////////////
		if (input[i] == '\'')
			through_singlequotes(msh, input, &i, &j);
		if (input[i] == '$')
		{
			msh->exp_input = ft_strjoin2(msh->exp_input, \
								find_value(msh->envp2, input, &i));
			if (!msh->exp_input)
				return (NULL);
			j = ft_strlen(msh->exp_input);
			msh->exp_input = ft_realloc(msh->exp_input, j, j + ft_strlen(input) - i);
		}
		// ft_printf(BLUE"input[i] = %c\n"NO_ALL, input[i]);/////////////////////////////////////
		if (input[i] && input[i] !='"' && input[i] !='\'' && input[i] !='$')
			msh->exp_input[j++] = input [i++];
	}
	ft_printf(MAGENTA"msh->Exp_input88 = %s\n"NO_ALL, msh->exp_input);/////////////////////////////
	return (msh->exp_input);
}

// Expands the Environment variables from the input string.
// An error message is diplayed if outer quotes are unclosed.
char	*ft_parse_and_expand(t_msh *msh, char *input)
{
	if (!input[0])
		return (NULL);
	if (ft_parse_input(msh, input) < 0)
		return (NULL);
	msh->exp_input = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!msh->exp_input)
		return (NULL);
	msh->exp_input = ft_expandedcpy(msh, input);
	printf(MAGENTA"msh->Exp_input = %s\n"NO_ALL, msh->exp_input);/////////////////
	return (msh->exp_input);
}
