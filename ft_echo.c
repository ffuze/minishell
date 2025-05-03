#include "minishell.h"

static int	handle_single_quotes(t_token *token)
{
	size_t	i;

	i = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] != '\'')
			printf("%c", token->value[i]);
		i++;
	}
	return (0);
}

static int	handle_double_quotes(t_token *token)
{
	size_t	i;

	i = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] != '"')
			printf("%c", token->value[i]);
		i++;
	}
	return (0);
}

int	check_flag(t_token **token, int j)
{
	int	i;

	i = 0;
	if (!token[j] || token[j]->type != TOKEN_WORD)
		return (j);
	while (token[j]->value[i] == ' ')
		i++;
	if (token[j]->value[i] == '-' && token[j]->value[i + 1] == 'n')
	{
		i++;
		while (token[j]->value[i] == 'n')
			i++;
		if (token[j]->value[i] == '\0')
			return (j);
	}
	// while (token[j] == "-n")
	// 	j++;
	return (check_flag(token, j + 1));
}

void	print_token(t_token *token, int *in_quotes)
{
	size_t	i;

	i = 0;
	while (token->value[i])
	{
		if (!(*in_quotes) && token->value[i] == ';')
			return ;
		else if (!(*in_quotes) && token->value[i] == '\\')
			continue ;
		else if (token->value[i] == '\'' || token->value[i] == '"')
			*in_quotes = !(*in_quotes); // mette in_quotes da 1 a 0
		else
			printf("%c", token->value[i]);
		i++;
	}
}

void	ft_echo(t_token **tokens)
{
	int	i;
	int	newline;
	int	in_quotes;

	i = check_flag(tokens, 0);
	newline = 1;
	in_quotes = 0;
	if (i >= 0 && tokens[i])
	{
		newline = 0;
		i++;
	}
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_STRING_SINGLE)
			handle_single_quotes(tokens[i]);
		else if (tokens[i]->type == TOKEN_STRING_DOUBLE)
			handle_double_quotes(tokens[i]);
		else
			print_token(tokens[i], &in_quotes);
		if (tokens[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
