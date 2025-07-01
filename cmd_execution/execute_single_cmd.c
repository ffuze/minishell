#include "../minishell.h"

static void	child_proc(t_msh *msh)
{
	msh->fd_mrx = NULL;
	setup_signals();
	if (msh->cmds->abort_flag)
	{
		free_everything(*msh);
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
		execute_builtin_commands(msh, msh->cmds->cmd);
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
		id = fork();
	if (id < 0)
		return ;
	else if (0 == id)
		child_proc(msh);
	while (waitpid(id, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
	}
}
