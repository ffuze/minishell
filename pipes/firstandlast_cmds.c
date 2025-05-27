#include "../minishell.h"

int	first_cmd_process(t_msh *msh, int *pipefd)
{
	close(pipefd[0]);
	if (msh->tokens[0]->type == TOKEN_RE_INPUT)
	{
		handle_input_redirection(msh);
		redirect_input(msh);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(pipefd[1]), 0);
	close(pipefd[1]);
	execute_cmd(msh->cmds->cmd, msh->envp2);
	return (1);
}

int	last_cmd_process(t_msh *msh, int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (close(pipefd[0]), 0);
	close(pipefd[0]);
	if (msh->outfi_flag)
	{
		// handle_output_redirection(msh);
		redirect_output(msh);
	}
	execute_cmd(msh->cmds->cmd, msh->envp2);
	return (1);
}
