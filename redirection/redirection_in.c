#include "../minishell.h"

// Substitutes the standard input with a file.
void redirect_input(t_msh *msh)
{
	int infile_fd;

	if (msh->infiles->heredoc_flag && msh->infiles->heredoc_flag)
		return ;
	if (!msh->infiles->infile)
		return ;
	ft_printf(BRCYAN"Infile: %s\n"NO_ALL, msh->infiles->infile);
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
int setup_input_redirection(t_msh *msh)
{
	msh->infiles = malloc(sizeof(t_inf));
	msh->infiles->heredoc_executed = false;
	if (!msh->infiles)
		exit(0);
	msh->infiles->heredoc_flag = malloc(sizeof(bool));
	if (!msh->infiles->heredoc_flag)
	{
		free(msh->infiles);
		exit(0);
	}
	if (ft_strcmp(msh->tokens[0]->value, "<") == 0)
	{
		msh->infiles->heredoc_flag = false;
		msh->infiles->infile = ft_strdup(msh->tokens[1]->value);
		if (!msh->infiles->infile)
		{
			// free(msh->infiles->heredoc_flag);
			free(msh->infiles);
			exit(0);
		}
		redirect_input(msh);
	}
	else if (ft_strcmp(msh->tokens[0]->value, "<<") == 0)
	{
		msh->infiles->heredoc_flag = true;
		msh->infiles->infile = NULL;
		if (!msh->infiles->heredoc_executed)
		{
			read_heredoc(msh->tokens[1]->value);
			msh->infiles->heredoc_executed = true;
		}
		// Parent process call.
		// For the child process check execute_redirection() in exeggutor.c
		// read_heredoc(msh);
	}
	return (1);
}
