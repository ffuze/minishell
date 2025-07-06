/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:06:04 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/01 21:29:34 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_pipeline(t_msh *msh)
{
	int		i;
	int		status;
	t_cmds	*current;

	current = msh->cmds;
	if (!current)
		return (print_err("No commands to execute.", "\n"));
	status = 0;
	i = 0;
	setup_signals_cmd();
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
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
	}
	setup_signals();
}

// Determines whether a single command or more have to be executed.
void	pipe_check(t_msh *msh)
{
	msh->pipe_counter = msh->pipe_number;
	if (!msh->cmds)
	{
		ft_printf("Error: no commands to execute\n");
		return ;
	}
	if (msh->pipe_counter > 0)
		init_pipeline(msh);
	else if (msh->pipe_counter == 0)
		execute_single_cmd(msh);
}
