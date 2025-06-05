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

static size_t	through_doublequotes(char **envp, char *input, char *clean_input, size_t *i)
{
	size_t	j;

	j = ft_strlen(clean_input);
	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		if (!envp)
			return (0);// da eliminare
		if (input[*i] == '$')
		{
			clean_input = ft_strjoin2(clean_input, find_value(envp, input, i));
			if (!clean_input)
				return (0);
			j = ft_strlen(clean_input);
			clean_input = ft_realloc(clean_input, j, ft_strlen(input) - *i);
			(*i)++;
		}
		if (input[*i] && input[*i] != '$')
		{
			clean_input[j] = input[*i];
			j++;
			(*i)++;
		}
	}
	if (input[*i])
		(*i)++;
	return (j);
}

static void	through_singlequotes(char *input, char *clean_input, size_t *i, size_t *j)
{
	(*i)++;
	while (input[*i] && input[*i] != '\'')
	{
		clean_input[*j] = input [*i];
		(*j)++;
		(*i)++;
	}
	if (input[*i])
		(*i)++;
}

// Returns the string "input" without outer quotes.
char	*ft_cleancpy(char **envp, char *input, char *clean_input)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			j += through_doublequotes(envp, input, clean_input, &i);
			if ( j == 0)
				return (ft_printf(RED"DANGERDANGERDANGER"NO_ALL), NULL);///////////////////
		}
		if (input[i] == '\'')
			through_singlequotes(input, clean_input, &i, &j);
		if (input[i] == '$')
		{
			clean_input = ft_strjoin2(clean_input, find_value(envp, input, &i));
			if (!clean_input)
				return (NULL);
			j = ft_strlen(clean_input);
			clean_input = ft_realloc(clean_input, j, ft_strlen(input) - i);
		}
		if (input[i] && input[i] !='"' && input[i] !='\'')
			clean_input[j++] = input [i++];
	}
	printf(MAGENTA"Clean_input88 = %s\n"NO_ALL, clean_input);
	return (clean_input);
}

// Returns the string input without quotes (except those between a pair of
// quotes of a different type).
// An error message is diplayed if outer quotes are unclosed.
char	*ft_remove_quotes(char **envp, char *input)// Gestire qui l'espansione delle variabili
{
	// char	*expanded_inpt;
	char	*clean_input;
	size_t	l;

	if (!input[0])
		return (NULL);
	// expanded_inpt = ft_expand_var(envp, input);
	l = ft_clean_input_len(input);
	if (l < 0)
		return (NULL);
	clean_input = ft_calloc(l + 1, sizeof(char *));
	if (!clean_input)
		return (NULL);
	clean_input = ft_cleancpy(envp, input, clean_input);
	printf(MAGENTA"Clean_input = %s\n"NO_ALL, clean_input);
	return (clean_input);
}
