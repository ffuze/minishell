#include "../minishell.h"

void redirect_input(t_msh *msh)
{
	int infile_fd;

	infile_fd = 0;
	ft_printf(BRCYAN"infile: %s\n"NO_ALL, msh->infiles->infile);
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
	}
	dup2(infile_fd, 0);
	close(infile_fd);
}

int handle_input_redirection(t_msh *msh)
{
	int     i;
	
	i = 0;
	if (!msh->infiles)
	{
		printf("Missing input file for redirection\n");
		msh->exit_status = 1;
		return (0);
	}
	while (msh->tokens[i])
	{
		if (msh->tokens[i]->type == TOKEN_RE_INPUT && msh->tokens[i + 1])
		{
			msh->infiles = malloc(sizeof(t_inf));
			if (!msh->infiles)
				return 0;
			msh->infiles->infile = ft_strdup(msh->tokens[i + 1]->value);
			if (!msh->infiles->infile)
				return (0);
			msh->infiles->next = NULL;
			msh->infiles = msh->infiles->next;
			i++;
		}
		i++;
	}
	return (1);
}
