#include "../minishell.h"

static int	first_cmd_process(t_msh *msh, t_cmds *current, int *pipefd, char *input)
{
	setup_signals();
	close(pipefd[0]);
	if (msh->tokens[0]->type == TOKEN_RE_INPUT)
	{
		setup_input_redirection(msh);
		redirect_input(msh);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(pipefd[1]), 0);
	close(pipefd[1]);
	execute_cmd(msh, current->cmd, msh->envp2, input);
	return (1);
}

// Initializes the first command in the pipeline.
void	init_firstcmd(t_msh *msh, t_cmds *current, int *i, char *input)
{
	int	id1;

	id1 = fork();
	if (id1 < 0)
		return (print_err("Fork failed for id1.", "\n"));
	else if (0 == id1)
		first_cmd_process(msh, current, msh->fd_mrx[*i], input);
}
