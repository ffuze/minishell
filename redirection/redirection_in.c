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
		free_everything(*msh);
		exit(1);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
}

// Fills the infile structure with the appropriate file name, and determines
// whether there is an input file or a heredoc.
/* int setup_input_redirection(t_msh *msh)
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
} */
