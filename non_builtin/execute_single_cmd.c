#include "../minishell.h"

static void	child_proc(t_msh *msh, char *input)
{
	if (msh->tokens[0]->type == TOKEN_RE_INPUT)
	{
		setup_input_redirection(msh);
		redirect_input(msh);
	}
	else if (msh->outfi_flag)
	{
		setup_output_redirection(msh);
		redirect_output(msh);
	}
	execute_cmd(msh, msh->cmds->cmd, msh->envp2, input);
}

void	execute_single_cmd(t_msh *msh, char *input)
{
	pid_t	id;
	int status;

	id = 1;
	status = 0;
	if (ft_strcmp(msh->cmds->cmd[0], "exit") == 0 || \
			ft_strcmp(msh->cmds->cmd[0], "clear") == 0)
		execute_builtin_commands(msh, msh->cmds->cmd, input);
	else
		id = fork();
	if (id < 0)
		return ;
	else if (0 == id)
	{
		setup_signals();
		ft_printf("Process ID: %d\n", getpid());///////////////////////////////////
		child_proc(msh, input);
	}
	while (waitpid(id, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
	}
}
