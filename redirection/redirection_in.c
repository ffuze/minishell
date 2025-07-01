#include "../minishell.h"

// Substitutes the standard input with a file.
void	redirect_input(t_msh *msh, t_cmds *current)
{
	int		infile_fd;

	if (!current->infile)
		return ;
	infile_fd = open(current->infile, O_RDONLY, 0644);
	if (infile_fd < 0)
	{
		print_err(current->infile, ": could not be opened.\n");
		free_cmd_list(msh->cmds);
		free_stuff(*msh);
		exit(1);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
}
