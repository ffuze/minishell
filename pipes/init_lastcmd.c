#include "../minishell.h"

static int	last_cmd_process(t_msh *msh, t_cmds *current, int *pipefd, char *input)
{
	setup_signals();
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (close(pipefd[0]), 0);
	close(pipefd[0]);
	if (msh->outfi_flag)
	{
		setup_output_redirection(msh);
		redirect_output(msh);
	}
	execute_cmd(msh, current->cmd, msh->envp2, input);
	return (1);
}

static int	setup_builtin_last(t_msh *msh, t_cmds *current, int *i, char *input)
{
	setup_signals();
	close(msh->fd_mrx[*i][1]);
	// Check per redirection output.
	close(msh->fd_mrx[*i][0]);
	execute_builtin_commands(msh, current->cmd, input);
	return (1);
}

// Initializes the last command in the pipeline.
void	init_lastcmd(t_msh *msh, t_cmds *current, int *i, char *input)
{
	int	id3;

	id3 = 1;
	if (identify_builtin_commands(msh, current->cmd))
		setup_builtin_last(msh, current, i, input);
	else
		id3 = fork();
	if (id3 < 0)
		return (print_err("Fork failed for id3.", "\n"));
	else if (0 == id3)
		last_cmd_process(msh, current, msh->fd_mrx[*i], input);
}
