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
		exit(1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

// Fills the outfile structure with the appropriate file name, and determines
// whether to overwrite or append the content.
int	setup_output_redirection(t_msh *msh)
{
	int		i;
	
	i = 0;
	while (msh->tokens[i] && msh->tokens[i]->type != TOKEN_OUTFILE)
		i++;
	// ft_printf(BRCYAN">>>>>>>>>>>>>\n"NO_ALL);/////////////////
	msh->outfiles = malloc(sizeof(t_outf) * 2);// *2?
	if (!msh->outfiles)
		exit(0);
	msh->outfiles->outfile = ft_strdup(msh->tokens[i]->value);
	if (!msh->outfiles->outfile)
	{
		free(msh->outfiles);
		exit(0);
	}
	msh->outfiles->append_flag = malloc(sizeof(bool));
	if (ft_strcmp(msh->tokens[0]->value, ">") == 0)
	{
		msh->outfiles->append_flag = false;
	}
	else if (ft_strcmp(msh->tokens[0]->value, ">>") == 0)
	{
		msh->outfiles->append_flag = true;
	}
	return (1);
}
