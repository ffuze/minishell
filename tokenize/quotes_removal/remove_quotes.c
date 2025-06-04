#include "../../minishell.h"

static void	through_doublequotes(char *input, char *clean_input, int *i, int *j)
{
	(*i)++;
	while (input[*i] && input[*i] != '"')
	{
		clean_input[*j] = input [*i];
		(*j)++;
		(*i)++;
	}
	if (input[*i])
		(*i)++;
}

static void	through_singlequotes(char *input, char *clean_input, int *i, int *j)
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
void	ft_cleancpy(char *input, char *clean_input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '"')
			through_singlequotes(input, clean_input, &i, &j);
		if (input[i] == '\'')
			through_doublequotes(input, clean_input, &i, &j);
		if (!input[i])
			return;
		clean_input[j++] = input [i++];
	}
}

// Returns the string input without quotes (except those between a pair of
// quotes of a different type).
// An error message is diplayed if outer quotes are unclosed.
char	*ft_remove_quotes(char *input)// Gestire qui l'espansione delle variabili
{
	char	*clean_input;
	int		l;

	if (!input[0])
		return (NULL);
	l = ft_clean_input_len(input);
	if (l < 0)
		return (NULL);
	clean_input = ft_calloc((size_t)l + 1, sizeof(char *));
	if (!clean_input)
		return (NULL);
	ft_cleancpy(input, clean_input);
	printf(MAGENTA"Clean_input = %s\n"NO_ALL, clean_input);
	return (clean_input);
}
