#include "../minishell.h"

// Substitutes the standard output with a file.
void	redirect_output(t_msh *msh, t_cmds *current)
{
	int		outfile_fd;

	if (!current->outfile)
		return ;
	if (current->append_flag)
		outfile_fd = open(current->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile_fd = open(current->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		print_err(current->outfile, ": could not be opened.\n");
		free_cmd_list(msh->cmds);
		free_everything(*msh);
		exit(1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}
