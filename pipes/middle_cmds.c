#include "../minishell.h"

// pipefd1: fd_mrx[*i - 1]
// pipefd2: fd_mrx[*i]
int	middle_cmd_process(t_msh *msh, char **cmd, int *i, char *input)
{
	setup_signals();
	close(msh->fd_mrx[*i][0]);
	if (ft_strcmp(cmd[0], "clear") == 0 || \
					ft_strcmp(cmd[0], "exit") == 0)
	{
		close(msh->fd_mrx[*i - 1][0]);
		close(msh->fd_mrx[*i][1]);
		liberate_fdmatrix(msh->fd_mrx, msh->pipe_count);
		free_everything(*msh, input);
		free_cmd_list(msh->cmds);
		exit(EXIT_SUCCESS);
	}
	if (dup2(msh->fd_mrx[*i - 1][0], STDIN_FILENO) < 0)
		return (close(msh->fd_mrx[*i - 1][0]), close(msh->fd_mrx[*i][1]), 0);
	if (dup2(msh->fd_mrx[*i][1], STDOUT_FILENO) < 0)
		return (close(msh->fd_mrx[*i][1]), 0);
	close(msh->fd_mrx[*i][1]);
	if (identify_builtin_commands(msh, cmd))
		close(msh->fd_mrx[*i][0]);
	execute_cmd(msh, cmd, msh->envp2, input);
	return (1);
}

// Creates a child process and a pipe for each command to be executed
//  between the first and last.
int	middle_child_generator(t_msh *msh, t_cmds *current, char *input)
{
	int		id2;
	int		i;

	i = 0;
	while (msh->pipe_count)
	{
		i++;
		if (-1 == pipe(msh->fd_mrx[i]))
			return (print_err("Failed to create pipe.", "\n"), i);
		id2 = fork();
		if (id2 < 0)
			return (print_err("Fork failed for id2.", "\n"), \
						close(msh->fd_mrx[i][0]), close(msh->fd_mrx[i][1]), i - 1);
		else if (0 == id2)
		{
			middle_cmd_process(msh, current->cmd, &i, input);
		}
		close(msh->fd_mrx[i - 1][0]);
		close(msh->fd_mrx[i][1]);
		msh->pipe_count--;
		*current = *current->next;
	}
	return (i);
}
