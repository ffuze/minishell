#include "../minishell.h"

void	redirect_output(t_msh *msh)
{
	int		outfile_fd;
	char	*outfile;

	outfile = msh->outfiles->outfile;
	ft_printf(BRCYAN"outfile: %s\n"NO_ALL, outfile);////////////////
	if (msh->outfiles->append_flag)
		outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		print_err(msh->outfiles->outfile, ": could not be opened.\n");
		exit(1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

// int	handle_output_redirection(t_msh *msh)