#include "../minishell.h"

static void	init_firstcmd(t_msh *msh, t_cmds *current, int *i, char *input)
{
	int	id1;

	id1 = fork();
	if (id1 < 0)
		return (print_err("Fork failed for id1.", "\n"));
	if (0 == id1)
		first_cmd_process(msh, current, msh->fd_mrx[*i], input);
}

static void	init_lastcmd(t_msh *msh, t_cmds *current, int *i, char *input)
{
	int	id3;

	id3 = 1;
	if (ft_strcmp(current->cmd[0], "exit") == 0 || \
			ft_strcmp(current->cmd[0], "clear") == 0)
		identify_builtin_commands(msh, current->cmd, input);
	else
		id3 = fork();
	if (id3 < 0)
		return (print_err("Fork failed for id3.", "\n"));
	else if (0 == id3)
		last_cmd_process(msh, current, msh->fd_mrx[*i], input);
}

static void	init_pipeline(t_msh *msh, char *input)
{
	int		i;
	int 	status;
	t_cmds	*current;

	current = msh->cmds;
	if (!current)
		return (print_err("No commands to execute.", "\n"));
	status = 0;
	i = 0;
	msh->fd_mrx = fd_matrix_creator(msh->pipe_count);
	if (-1 == pipe(msh->fd_mrx[i]))
		return (print_err("Failed to create pipe.", "\n"));
	init_firstcmd(msh, current, &i, input);
	current = current->next;
	close(msh->fd_mrx[i][1]);
	msh->pipe_count--;
	i = middle_child_generator(msh, current, input);
	current = current->next;
	init_lastcmd(msh, current, &i, input);
	liberate_fdmatrix(msh->fd_mrx, msh->pipe_count);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))// Prende lo status dell'ultimo processo a uscire invece
			msh->exit_status = WEXITSTATUS(status); // che dall'ultimo della pipeline.
		// bash$ cat | wc *file senza permessi* ---> cat aspettera' l'input quindi
		// si conclude per ultimo ma l'exit status deve essere quello di wc
	}
}

// Determines whether a single command or more have to be executed.
void	pipe_check(t_msh *msh, char *input)
{
	unsigned char	code;

	code = 0;
	if (msh->pipe_count > 0)
		init_pipeline(msh, input);
	else if (msh->pipe_count == 0)
	{
		if (identify_builtin_commands(msh, msh->cmds->cmd, input) == 0)
			execute_single_cmd(msh, input);
	}
}
