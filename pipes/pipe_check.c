#include "../minishell.h"

//-----------------------------------------------------------------------------
// Closes all file descriptors and liberates the allocated memory
void	liberate_fdmatrix(int **fd_mrx, int pipe_count)
{
	int	j;

	j = 0;
	while (j < pipe_count)
	{
		close(fd_mrx[j][0]);
		close(fd_mrx[j][1]);
		free(fd_mrx[j]);
		j++;
	}
	free(fd_mrx);
}

int	**fd_matrix_creator(int pipe_count)
{
	int	**fd_matrix;
	int	i;

	i = 0;
	fd_matrix = ft_calloc((pipe_count + 1), sizeof(int *));
	if (!fd_matrix)
		exit(0);
	while (i < (pipe_count))
	{
		fd_matrix[i] = ft_calloc(2, sizeof(int));
		if (!fd_matrix[i])
		{
			liberate_fdmatrix(fd_matrix, i);
			exit(0);
		}
		i++;
	}
	return (fd_matrix);
}
//-----------------------------------------------------------------------------

int	middle_cmd_process(char **cmd, char **envp2, int *pipefd1, int *pipefd2)
{
	close(pipefd2[0]);
	if (dup2(pipefd1[0], STDIN_FILENO) < 0)
		return (close(pipefd1[0]), close(pipefd2[1]), 0);
	close(pipefd1[0]);
	if (dup2(pipefd2[1], STDOUT_FILENO) < 0)
		return (close(pipefd2[1]), 0);
	close(pipefd2[1]);
	execute_cmd(cmd, envp2);
	return (1);
}

// Creates a child process and a pipe for each command to be executed
//  between the first and last.
static int	middle_child_generator(t_msh *msh)
{
	t_cmds *current;
	int		id2;
	int		i;

	i = 0;
	current = msh->cmds;
	while (msh->pipe_count/* i < (msh->cmds_count - 1) */)
	{
		i++;
		if (-1 == pipe(msh->fd_mrx[i]))
			return (print_err("Failed to create pipe.", "\n"), i);
		id2 = fork();
		if (id2 < 0)
			return (print_err("Fork failed for id2.", "\n"), \
							close(msh->fd_mrx[i][0]), close(msh->fd_mrx[i][1]), i - 1);
		else if (0 == id2)
			middle_cmd_process(current->cmd, msh->envp2, msh->fd_mrx[i - 1], msh->fd_mrx[i]);
		close(msh->fd_mrx[i][1]);
		msh->pipe_count--;
		current = current->next;
	}
	return (i);
}
//-----------------------------------------------------------------------------

int	first_cmd_process(char **cmd, char **envp, int *pipefd)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		return (close(pipefd[1]), 0);
	close(pipefd[1]);
	execute_cmd(cmd, envp);
	return (1);
}

int	last_cmd_process(char **cmd, char **envp, int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		return (close(pipefd[0]), 0);
	close(pipefd[0]);
	execute_cmd(cmd, envp);
	return (1);
}

//-----------------------------------------------------------------------------
void	pipe_check(t_msh *msh)
{
	int	i;
	int	id1;
	int	id3;

	i = 0;
	if (msh->pipe_count > 0)
	{
		msh->fd_mrx = fd_matrix_creator(msh->pipe_count);

		if (-1 == pipe(msh->fd_mrx[i]))
		return (print_err("Failed to create pipe.", "\n"));

		id1 = fork();
		if (id1 < 0)
			return (print_err("Fork failed for id1.", "\n"));
		if (0 == id1)
			first_cmd_process(msh->cmds->cmd, msh->envp2, msh->fd_mrx[i]);
		msh->cmds = msh->cmds->next;

		close(msh->fd_mrx[i][1]);
		msh->pipe_count--;
		i = middle_child_generator(msh);
		msh->cmds = msh->cmds->next;

		id3 = fork();
		if (id3 < 0)
			return (print_err("Fork failed for id3.", "\n"));
		else if (0 == id3)
			last_cmd_process(msh->cmds->cmd, msh->envp2, msh->fd_mrx[i]);

		liberate_fdmatrix(msh->fd_mrx, msh->pipe_count);
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	else if (msh->pipe_count == 0)
	{
		execute_regular(msh);
		// if (msh->outfi_flag)
		// {}
	}
}
