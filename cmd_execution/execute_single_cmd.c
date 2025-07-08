/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <adegl-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:48:27 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/08 15:37:39 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_proc(t_msh *msh)
{
	msh->fd_mrx = NULL;
	reset_child_signals();
	if (msh->cmds->abort_flag)
	{
		free_stuff(*msh);
		free_cmd_list(msh->cmds);
		msh->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (msh->cmds->infile)
		redirect_input(msh, msh->cmds);
	if (msh->cmds->outfile)
		redirect_output(msh, msh->cmds);
	execute_cmd(msh, msh->cmds->cmd, msh->envp2);
}

static void	init_builtin(t_msh *msh)
{
	int	i;
	int	o;

	if (msh->cmds->abort_flag)
	{
		msh->exit_status = 1;
		return ;
	}
	if (ft_strcmp(msh->cmds->cmd[0], "exit") == 0)
	{
		execute_builtin_commands(msh, msh->cmds->cmd);
		return ;
	}
	i = dup(STDIN_FILENO);
	o = dup(STDOUT_FILENO);
	if (msh->cmds->infile)
		redirect_input(msh, msh->cmds);
	if (msh->cmds->outfile)
		redirect_output(msh, msh->cmds);
	execute_builtin_commands(msh, msh->cmds->cmd);
	dup2(i, STDIN_FILENO);
	dup2(o, STDOUT_FILENO);
	close(i);
	close(o);
}

// Initializes a command when no pipes are present.
void	execute_single_cmd(t_msh *msh)
{
	pid_t	id;
	int		status;

	status = 0;
	if (!msh || !msh->cmds || !msh->cmds->cmd)
	{
		ft_printfd(2, RED"Error: No commands found\n"NO_ALL);
		return ;
	}
	if (identify_builtin_commands(msh->cmds->cmd))
		return (init_builtin(msh));
	else
	{
		setup_signals_cmd();
		id = fork();
	}
	if (id < 0)
	{
		setup_signals();
		return ;
	}
	else if (0 == id)
		child_proc(msh);
	while (waitpid(id, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
				msh->exit_status = 130;
			else if (sig == SIGQUIT)
			{
				write(STDOUT_FILENO, "Quit\n", 19);
				msh->exit_status = 131;
			}
		}
	}
	setup_signals();
}
