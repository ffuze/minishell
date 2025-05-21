#include "../minishell.h"

static void	init_firstcmd(t_msh *msh, int *i)
{
	int	id1;

	id1 = fork();
	if (id1 < 0)
		return (print_err("Fork failed for id1.", "\n"));
	if (0 == id1)
		first_cmd_process(msh, msh->fd_mrx[*i]);
}

static void	init_lastcmd(t_msh *msh, int *i)
{
	int	id3;

	id3 = fork();
	if (id3 < 0)
		return (print_err("Fork failed for id3.", "\n"));
	else if (0 == id3)
		last_cmd_process(msh->cmds->cmd, msh->envp2, msh->fd_mrx[*i]);
}

static void	init_pipeline(t_msh *msh)
{
	int	i;
	
	i = 0;
	msh->fd_mrx = fd_matrix_creator(msh->pipe_count);
	if (-1 == pipe(msh->fd_mrx[i]))
		return (print_err("Failed to create pipe.", "\n"));
	init_firstcmd(msh, &i);
	msh->cmds = msh->cmds->next;
	close(msh->fd_mrx[i][1]);
	msh->pipe_count--;
	i = middle_child_generator(msh);
	msh->cmds = msh->cmds->next;
	init_lastcmd(msh, &i);
	liberate_fdmatrix(msh->fd_mrx, msh->pipe_count);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

// Determines whether a single command or more have to be executed.
void	pipe_check(t_msh *msh)
{
	if (msh->pipe_count > 0)
		init_pipeline(msh);
	else if (msh->pipe_count == 0)
		execute_single_cmd(msh);
}
