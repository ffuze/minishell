#include "../minishell.h"

// Substitutes the standard input with a file.
void	redirect_input(t_msh *msh)
{
	int	infile_fd;

	infile_fd = 0;
	ft_printf(BRCYAN"Infile: %s\n"NO_ALL, msh->infiles->infile);////////////////
	infile_fd = open(msh->infiles->infile, O_RDONLY);
	if (infile_fd < 0)
	{
		print_err(msh->infiles->infile, ": Could not be opened\n");
		exit(1);
	}
	dup2(infile_fd, 0);
	close(infile_fd);
}

// Fills the infile structure with the appropriate file name, and determines
// whether there is an input file or a heredoc.
int	setup_input_redirection(t_msh *msh)
{
	msh->infiles = malloc(sizeof(t_inf));
	if (!msh->infiles)
		exit(0);
	msh->infiles->infile = ft_strdup(msh->tokens[1]->value);
	if (!msh->infiles->infile)
	{
		free(msh->infiles);
		exit(0);
	}
	msh->infiles->heredoc_flag = malloc(sizeof(bool));
	if (ft_strcmp(msh->tokens[0]->value, "<") == 0)
		redirect_input(msh);
	else if (ft_strcmp(msh->tokens[0]->value, "<<") == 0)
		read_heredoc(msh);
	return (1);
}
