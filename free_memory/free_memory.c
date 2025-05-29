#include "../minishell.h"

void	free_tokens(t_token **tokens)
{
	int i = 0;

	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void    free_everything(t_msh msh, char **split_input, char *input)
{
    free_tokens(msh.tokens);
	free_dpc(split_input);
	free_dpc(msh.envp2);
	free(input);
}
