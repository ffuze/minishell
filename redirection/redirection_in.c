#include "../minishell.h"

// Substitutes the standard input with a file
void	redirect_input(t_msh *msh)
{
	int infile_fd;
	infile_fd = 0;
	ft_printf(BRCYAN"Infile: %s\n"NO_ALL, msh->infiles->infile);////////////////
	while (msh->infiles)
	{
		infile_fd = open(msh->infiles->infile, O_RDONLY);
		if (infile_fd < 0)
		{
			print_err(msh->infiles->infile, ": Could not be opened\n");
			free_infiles(msh->infiles);
			exit(1);
		}
		msh->infiles = msh->infiles->next;
		if (msh->infiles)
			close(infile_fd);
	}
	dup2(infile_fd, 0);
	close(infile_fd);
}

// Fill the infile structure with the appropriate file name, and determines
// wether there is an input file or a heredoc
int	setup_input_redirection(t_msh *msh)
{
	int		i;
	t_inf	*infile;
	
	i = 0;
	infile = NULL;
	if (!msh->infiles)
	{
		printf("Missing input file for redirection\n");
		msh->exit_status = 1;
		return (0);
	}
	infile = ft_strdup(msh->tokens[i + 1]->value);
	if (!infile)
		return (0);
	if (ft_strcmp(msh->tokens[0]->value, ">") == 0)
		msh->infiles->heredoc_flag = false;
	else if (ft_strcmp(msh->tokens[0]->value, ">>") == 0)
	{
		// prende il delimitatore
		msh->infiles->heredoc_flag = true;
	}
	return (1);
}
