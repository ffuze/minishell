#include "minishell.h"

int	handle_double_quotes_echo(t_token *token)
{
	size_t	i;

	i = 0;
	while (token->value[i] != '\0' && token->value[i] != '"')
	{
		printf("token value: %c\n", token->value[i]);
		printf("%c", token->value[i]);
		i++;
	}
	return (0);
}

int	handle_single_quotes_echo(t_token *token)
{
	size_t	i;

	i = 0;
	while (token->value[i] != '\0' && token->value[i] != '\'')
	{
		printf("%c", token->value[i]);
		i++;
		if (token->value[i] == '"')
			handle_double_quotes_echo(token);
	}
	return (0);
}

int	check_flag(t_token **tokens, int j)
{
	int	i;

	while (tokens[j])
	{
		i = 0;
		if (tokens[j]->value[i] != '-' || tokens[j]->value[i + 1] != 'n')
			break;
		i++;
		while (tokens[j]->value[i] == 'n')
			i++;
		if (tokens[j]->value[i] != '\0')
			break;
		j++;
	}
	return (j);
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
	int	newline = 1;
	int	in_quotes = 0;

	i = check_flag(tokens, 1);
	if (i > 1)
		newline = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_STRING_SINGLE)
			handle_single_quotes_echo(tokens[i]);
		else if (tokens[i]->type == TOKEN_STRING_DOUBLE)
			handle_double_quotes_echo(tokens[i]);
		else
			print_token(tokens[i], &in_quotes);
		if (tokens[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
