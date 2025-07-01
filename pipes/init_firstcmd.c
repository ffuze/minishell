/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_firstcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:52:33 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/01 21:24:43 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	first_cmd_process(t_msh *msh, t_cmds *current, int *pipefd)
{
	setup_signals();
	close(pipefd[0]);
	if (ft_strcmp(current->cmd[0], "exit") == 0)
	{
		close(pipefd[1]);
		liberate_fdmatrix(msh->fd_mrx, msh->pipe_number);
		free_cmd_list(msh->cmds);
		free_stuff(*msh);
		exit(EXIT_SUCCESS);
	}
	if (current->infile)
		redirect_input(msh, current);
	if (current->outfile)
		redirect_output(msh, current);
	else if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(pipefd[1]), 0);
	close(pipefd[1]);
	execute_cmd(msh, current->cmd, msh->envp2);
	return (1);
}

// Initializes the first command in the pipeline.
void	init_firstcmd(t_msh *msh, t_cmds *current, int *i)
{
	int	id1;

	id1 = fork();
	if (id1 < 0)
		return (print_err("Fork failed for id1.", "\n"));
	else if (0 == id1)
	{
		if (!current || !current->cmd[0] || current->abort_flag)
		{
			liberate_fdmatrix(msh->fd_mrx, msh->pipe_number);
			free_cmd_list(msh->cmds);
			free_stuff(*msh);
			msh->exit_status = 1;
			exit(EXIT_FAILURE);
		}
		first_cmd_process(msh, current, msh->fd_mrx[*i]);
	}
}
