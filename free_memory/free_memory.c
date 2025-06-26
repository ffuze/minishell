#include "../minishell.h"

void	free_tokens(t_token **tokens)
{
	int i = 0;

	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void    free_everything(t_msh msh)
{
	free_dpc(msh.envp2);
    free_tokens(msh.tokens);
	free(msh.exp_input);
}

void	free_cmd_list(t_cmds *root)
{
	t_cmds	*tmp;

	if (!root)
		return ;
	while (root)
	{
		tmp = root->next;
		free(root->cmd);
		if (root->outfile)
			free(root->outfile);
		free(root);
		root = tmp;
	}
	tmp = NULL;
}
