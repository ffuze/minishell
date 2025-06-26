#include "../minishell.h"

static void	child_proc(t_msh *msh)
{
	if (msh->cmds->abort_flag)
	{
		liberate_fdmatrix(msh->fd_mrx, msh->pipe_number);
		free_everything(*msh);
		free_cmd_list(msh->cmds);
		msh->exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (msh->tokens[0]->type == TOKEN_RE_INPUT)
	{
		setup_input_redirection(msh);
		redirect_input(msh);
	}
	if (msh->cmds->outfile)
		redirect_output(msh, msh->cmds);
	execute_cmd(msh, msh->cmds->cmd, msh->envp2);
}

void	execute_single_cmd(t_msh *msh)
{
	pid_t	id;
	int status;

	id = 1;
	status = 0;
	if (!msh || !msh->cmds || !msh->cmds->cmd)
	{
		ft_printfd(2, RED"Error: No commands found\n"NO_ALL);
		return ;
	}
	if (ft_strcmp(msh->cmds->cmd[0], "exit") == 0)
		execute_builtin_commands(msh, msh->cmds->cmd);
	else
		id = fork();
	if (id < 0)
		return ;
	else if (0 == id)
	{
		setup_signals();
		msh->fd_mrx = NULL;
		ft_printf("Process ID: %d\n", getpid());///////////////////////////////////
		child_proc(msh);
	}
	while (waitpid(id, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
	}
}
