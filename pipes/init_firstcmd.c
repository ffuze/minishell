#include "../minishell.h"

static int	first_cmd_process(t_msh *msh, t_cmds *current, int *pipefd, char *input)
{
	setup_signals();
	close(pipefd[0]);
	if (ft_strcmp(current->cmd[0], "clear") == 0 || \
					ft_strcmp(current->cmd[0], "exit") == 0)
	{
		close(pipefd[1]);
		liberate_fdmatrix(msh->fd_mrx, msh->pipe_count);
		free_everything(*msh);
		free_cmd_list(msh->cmds);
		exit(EXIT_SUCCESS);
	}
	if (msh->tokens[1]->type == TOKEN_RE_INPUT)
	{
		setup_input_redirection(msh);
		redirect_input(msh);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(pipefd[1]), 0);
	close(pipefd[1]);
	if (identify_builtin_commands(msh, current->cmd))
		close(pipefd[0]);
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
