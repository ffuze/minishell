/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:03:17 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/01 21:03:18 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
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

void	free_stuff(t_msh msh)
{
	free_dpc(msh.envp2);
	free_tokens(msh.tokens);
	free(msh.exp_input);
}

void	free_input_redirection(t_cmds *current_node)
{
	if (current_node->infile)
	{
		if (current_node->heredoc_flag)
		{
			free(current_node->limiter);
			unlink(current_node->infile);
			current_node->heredoc_flag = false;
		}
		free(current_node->infile);
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
		if (root->cmd)
			free(root->cmd);
		if (root->outfile)
			free(root->outfile);
		free_input_redirection(root);
		free(root);
		root = tmp;
	}
	tmp = NULL;
}

void	free_everything(t_msh *msh)
{
	liberate_fdmatrix(msh->fd_mrx, msh->pipe_number);
	free_cmd_list(msh->cmds);
	free_stuff(*msh);
}
