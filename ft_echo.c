#include "minishell.h"

int	handle_single_quotes(t_token *token)
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

int	handle_double_quotes(t_token *token)
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

int	check_flag(t_token *token)
{
	int	i;

	i = 0;
	if (!token || token->type != TOKEN_WORD)
		return (0);
	while (token->value[i] == ' ')
		i++;
	if (token->value[i] == '-' && token->value[i + 1] == 'n')
	{
		i++;
		while (token->value[i] == 'n')
			i++;
		if (token->value[i] == '\0')
			return (1);
	}
	return (0);
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

	i = 1;
	newline = 1;
	in_quotes = 0;
	if (tokens[i] && check_flag(tokens[i]))
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
