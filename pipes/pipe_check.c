/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <adegl-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:06:04 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:58 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_status(t_msh *msh)
{
	int	status;
	int statuses[msh->pipe_number];
	int	sig;
	int i;

	i = 0;
	sig = 0;
	status = 0;
	while (waitpid(-1, &status, 0) && i < msh->pipe_number)
	{
		statuses[i] = status;
		
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			msh->exit_status = 128 + sig;
		}
		else if (i == msh->pipe_number - 1 && WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);// if not interrupted, last process's exit status
		i++;
	}
}

static void	init_pipeline(t_msh *msh)
{
	int		i;
	t_cmds	*current;

	current = msh->cmds;
	if (!current)
		return (print_err("No commands to execute.", "\n"));
	i = 0;
	setup_signals_heredoc();
	setup_signals_exec();
	msh->fd_mrx = fd_matrix_creator(msh->pipe_number);
	if (-1 == pipe(msh->fd_mrx[i]))
		return (print_err("Failed to create pipe.", "\n"));
	msh->pipe_counter--;
	init_firstcmd(msh, current, &i);
	current = current->next;
	close(msh->fd_mrx[i][1]);
	i = middle_child_generator(msh, &current);
	close(msh->fd_mrx[i][1]);
	init_lastcmd(msh, current, &i);
	liberate_fdmatrix(msh->fd_mrx, msh->pipe_number);
	get_status(msh);
}

// Determines whether a single command or more has to be executed.
void	pipe_check(t_msh *msh)
{
	msh->pipe_counter = msh->pipe_number;
	if (!msh->cmds)
	{
		ft_printfd(2, RED"Error: no commands to execute\n"NO_ALL);
		return ;
	}
	if (msh->pipe_counter > 0)
		init_pipeline(msh);
	else if (msh->pipe_counter == 0)
		execute_single_cmd(msh);
}
