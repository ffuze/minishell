#include "./minishell.h"

int	skip_spaces(t_token *input, int i)
{
	while (input->value[i] && input->value[i] == ' ')
		i++;
	return (i);
}