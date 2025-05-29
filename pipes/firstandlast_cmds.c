#include "../minishell.h"

int	first_cmd_process(t_msh *msh, t_cmds *current, int *pipefd)
{
	close(pipefd[0]);
	// ft_printf(BLUE"//////////////\n"NO_ALL);/////////////
	if (msh->tokens[0]->type == TOKEN_RE_INPUT)
	{
		// ft_printf(MAGENTA"//////////////\n"NO_ALL);/////////////
		setup_input_redirection(msh);
		redirect_input(msh);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(pipefd[1]), 0);
	close(pipefd[1]);
	execute_cmd(current->cmd, msh->envp2);
	return (1);
}

int	last_cmd_process(t_msh *msh, t_cmds *current, int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (close(pipefd[0]), 0);
	close(pipefd[0]);
	if (msh->outfi_flag)
	{
		// setup_output_redirection(msh);
		redirect_output(msh);
	}
	execute_cmd(current->cmd, msh->envp2);
	return (1);
}
