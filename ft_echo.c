#include "minishell.h"

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

void	print_token(t_token *token)
{
	printf("%s", token->value);
}

void	ft_echo(t_msh *msh)
{
	int	i;
	int	newline;

	newline = check_flag(msh->token[1]->value);
	if (i > 1)
		newline = 0;
	while (tokens[i] != NULL)
	{
		print_token(tokens[i]);
		if (tokens[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
