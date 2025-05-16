#include "../minishell.h"

int handle_input_redirection(t_msh *msh)
{
	int i;
	t_inf *new;
	t_inf *last;

	i = 0;
	last = NULL;
	if (!msh->infiles)
	{
		printf("Missing input file for redirection\n");
		msh->exit_status = 1;
		return (1);
	}
	while (msh->tokens[i])
	{
		if (msh->tokens[i]->type == TOKEN_RE_INPUT && msh->tokens[i + 1])
		{
			new = malloc(sizeof(t_inf *));
			if (!new)
				return (1);
			new->infile = msh->tokens[i + 1]->value;
			printf("valore di infile: %s\n", new->infile);
			new->next = NULL;
			if (!msh->infiles)
				msh->infiles = new;
			last = new;
		}
		i++;
	}
	return (0);
}
