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

void    free_everything(t_msh msh, char *input)
{
	free_dpc(msh.envp2);
    free_tokens(msh.tokens);
	free(msh.exp_input);
	free(input);
	if (msh.outfi_flag)
	{
		free(msh.outfiles->outfile);
		free(msh.outfiles);
	}
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
		free(root);
		root = tmp;
	}
	tmp = NULL;
}

void	free_output_redirection(t_msh *msh)
{
	if (msh->outfi_flag)
		free(msh->outfiles);
}
