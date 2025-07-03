/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:22:54 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/03 11:07:28 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// pipefd1: fd_mrx[*i - 1]
// pipefd2: fd_mrx[*i]
static int	middle_cmd_process(t_msh *msh, t_cmds *current, int *i)
{
	setup_signals();
	close(msh->fd_mrx[*i][0]);
	if (ft_strcmp(current->cmd[0], "exit") == 0)
	{
		close(msh->fd_mrx[*i - 1][0]);
		close(msh->fd_mrx[*i][1]);
		liberate_fdmatrix(msh->fd_mrx, msh->pipe_number);
		free_cmd_list(msh->cmds);
		free_stuff(*msh);
		exit(EXIT_SUCCESS);
	}
	if (current->infile)
		redirect_input(msh, current);
	else if (dup2(msh->fd_mrx[*i - 1][0], STDIN_FILENO) < 0)
		return (close(msh->fd_mrx[*i - 1][0]), close(msh->fd_mrx[*i][1]), 0);
	if (current->outfile)
		redirect_output(msh, current);
	else if (dup2(msh->fd_mrx[*i][1], STDOUT_FILENO) < 0)
		return (close(msh->fd_mrx[*i][1]), 0);
	close(msh->fd_mrx[*i - 1][0]);
	close(msh->fd_mrx[*i][1]);
	if (identify_builtin_commands(current->cmd))
		close(msh->fd_mrx[*i][0]);
	execute_cmd(msh, current->cmd, msh->envp2);
	return (1);
}

// Creates a child process and a pipe for each command to be executed
//  between the first and last.
int	middle_child_generator(t_msh *msh, t_cmds **current)
{
	int		id2;
	int		i;

	i = 0;
	while (msh->pipe_counter--)
	{
		i++;
		if (-1 == pipe(msh->fd_mrx[i]))
			return (print_err("Failed to create pipe.", "\n"), i);
		id2 = fork();
		if (id2 < 0)
			return (print_err("Fork failed for id2.", "\n"), \
					close(msh->fd_mrx[i][0]), close(msh->fd_mrx[i][1]), i - 1);
		else if (0 == id2)
		{
			if (!(*current) || !(*current)->cmd[0] || (*current)->abort_flag)
				return (free_everything(msh), msh->exit_status = 1, \
						exit(EXIT_FAILURE), i);
			middle_cmd_process(msh, *current, &i);
		}
		close(msh->fd_mrx[i - 1][0]);
		close(msh->fd_mrx[i][1]);
		*current = (*current)->next;
	}
	return (i);
}
