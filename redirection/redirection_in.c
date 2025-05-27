#include "../minishell.h"

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

int	handle_input_redirection(t_msh *msh)
{
	int i;
	t_inf *new;
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
			new = malloc(sizeof(t_inf));
			if (!new)
				return 0;
			new->infile = msh->tokens[i + 1]->value;
			new->next = NULL;
			if (!msh->infiles)
				msh->infiles = new;
			else
			{
				t_inf *temp = msh->infiles;
				while (temp->next)
					temp = temp->next;
				temp->next = new;
			}
		}
		i++;
	}
	return (1);
}
