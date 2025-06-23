#include "../minishell.h"

// Substitutes the standard output with a file.
void	redirect_output(t_msh *msh)
{
	int		outfile_fd;

	ft_printf(BRCYAN"outfile: %s\n"NO_ALL, msh->outfiles->outfile);////////////////
	if (msh->outfiles->append_flag)
		outfile_fd = open(msh->outfiles->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile_fd = open(msh->outfiles->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		print_err(msh->outfiles->outfile, ": could not be opened.\n");
		exit(1);/////////////////////////////free memory////////////////////////////////////////////
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

// Fills the outfile structure with the appropriate file name, and determines
// whether to overwrite or append the content.
int	setup_output_redirection(t_msh *msh)
{
	int		i;
	int		last_outfile_index;
	int		fd;

	i = 0;
	last_outfile_index = -1;
	while (msh->tokens[i])
	{
		if (msh->tokens[i]->type == TOKEN_OUTFILE)
		{
			fd = open(msh->tokens[i]->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd >= 0)
				close(fd);
			else
			{
				ft_printf(msh->tokens[i]->value, ": could not be created\n");
				return (0);
			}
			last_outfile_index = i;
		}
		i++;
	}
	if (last_outfile_index == -1 || !msh->outfiles)
		return (0);
	msh->outfiles->outfile = ft_strdup(msh->tokens[last_outfile_index]->value);
	if (!msh->outfiles->outfile)
	{
		free(msh->outfiles);
		return (0);
	}
	return (1);
}
