#include "../../minishell.h"

// Searches the var in the environment and returns its value.
char	*find_value(char **envp, char *input, size_t *i)
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
	if(!var_name || !var_name[0])
		return (free(var_name), "$");
	name_l = ft_strlen(var_name);
	while (envp[j])
	{
		if (ft_strncmp(envp[j], var_name, name_l) == 0)
			return (free(var_name), ft_strchr2(envp[j], '='));
		j++;
	}
	return (free(var_name), "");
}

// Expands environment variables and/or the exit status.
// Return 0 on failure.
int	expand_dollar(t_msh *msh, char *input, size_t *i, size_t *j)
{
	if (input[(*i) + 1] == '?')
	{
		msh->exp_input = ft_strjoin3(msh->exp_input, \
										ft_itoa(msh->exit_status));
		(*i) += 2;
	}
	else
	{
		msh->exp_input = ft_strjoin2(msh->exp_input, \
						find_value(msh->envp2, input, i));
	}
	if (!msh->exp_input)
		return (0);
	*j = ft_strlen(msh->exp_input);
	msh->exp_input = ft_realloc(msh->exp_input, *j, \
										*j + ft_strlen(input) - *i);
	return (1);
}
