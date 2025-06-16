#include "../minishell.h"

// !!!!! Exit in middle_cmd dara' un mondo di leak.

int	middle_cmd_process(t_msh *msh, char **cmd, int *pipefd1, int *pipefd2)
{
	setup_signals();
	close(pipefd2[0]);
	if (ft_strcmp(cmd[0], "clear") == 0 || \
					ft_strcmp(cmd[0], "exit") == 0)
	{
		close(pipefd1[0]);
		close(pipefd2[1]);
		exit(0);
	}
	if (dup2(pipefd1[0], STDIN_FILENO) < 0)
		return (close(pipefd1[0]), close(pipefd2[1]), 0);
	if (dup2(pipefd2[1], STDOUT_FILENO) < 0)
		return (close(pipefd2[1]), 0);
	close(pipefd2[1]);
	execute_cmd(msh, cmd, msh->envp2, "");
	return (1);
}
// 
// Creates a child process and a pipe for each command to be executed
//  between the first and last.
int	middle_child_generator(t_msh *msh, t_cmds *current, char *input)
{
	int		id2;
	int		i;

	(void)input;//////////////////
	i = 0;
	id2 = 1;
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
			middle_cmd_process(msh, current->cmd, msh->fd_mrx[i - 1], msh->fd_mrx[i]);
		}
		close(msh->fd_mrx[i - 1][0]);
		close(msh->fd_mrx[i][1]);
		msh->pipe_count--;
		current = current->next;
	}
	return (i);
}
