#include "../minishell.h"

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
	msh->fd_mrx = fd_matrix_creator(msh->pipe_number);
	if (-1 == pipe(msh->fd_mrx[i]))
		return (print_err("Failed to create pipe.", "\n"));
	msh->pipe_counter--;
	init_firstcmd(msh, current, &i, input);
	current = current->next;
	close(msh->fd_mrx[i][1]);
	i = middle_child_generator(msh, current, input);
	init_lastcmd(msh, current, &i, input);
	liberate_fdmatrix(msh->fd_mrx, msh->pipe_number);
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
	msh->pipe_counter = msh->pipe_number;
	if (!msh->cmds)
    {
        ft_printf("Error: no commands to execute\n");
        return;
    }
	if (msh->pipe_counter > 0)
		init_pipeline(msh, input);
	else if (msh->pipe_counter == 0)
	{
		if (execute_builtin_commands(msh, msh->cmds->cmd, input) == 0)
			execute_single_cmd(msh, input);
	}
}
