#include "../minishell.h"

static void	child_proc(t_msh *msh)
{
	if (msh->tokens[0]->type == TOKEN_RE_INPUT)
		{
			setup_input_redirection(msh);
			redirect_input(msh);
		}
	if (msh->outfi_flag)
		{
			setup_output_redirection(msh);
			redirect_output(msh);
		}
		execute_cmd(msh->cmds->cmd, msh->envp2);
}

void	execute_single_cmd(t_msh *msh)
{
	pid_t	id;
	int status;

	status = 0;
	id = fork();
	if (id < 0)
	{
		ft_putstr_fd("Fork failed.\n", 2);
		return ;
	}
	else if (0 == id)
	{
		child_proc(msh);
	}
	while (waitpid(id, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
	}
}
