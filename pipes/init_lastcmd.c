#include "../minishell.h"

static int	last_cmd_process(t_msh *msh, t_cmds *current, int *pipefd, char *input)
{
	setup_signals();
	close(pipefd[1]);
	if (ft_strcmp(current->cmd[0], "clear") == 0 || \
					ft_strcmp(current->cmd[0], "exit") == 0)
	{
		close(pipefd[0]);
		liberate_fdmatrix(msh->fd_mrx, msh->pipe_count);
		free_everything(*msh);
		free_cmd_list(msh->cmds);
		exit(EXIT_SUCCESS);
	}
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (close(pipefd[0]), 0);
	close(pipefd[0]);
	if (current->outfile)
	{
		redirect_output(msh, current);
	}
	execute_cmd(msh, current->cmd, msh->envp2, input);
	return (1);
}

// Initializes the last command in the pipeline.
void	init_lastcmd(t_msh *msh, t_cmds *current, int *i, char *input)
{
	int	id3;

	id3 = fork();
	if (id3 < 0)
		return (print_err("Fork failed for id3.", "\n"));
	else if (0 == id3)
		last_cmd_process(msh, current, msh->fd_mrx[*i], input);
}
