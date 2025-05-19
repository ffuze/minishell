#include "../minishell.h"

int handle_input_redirection(t_msh *msh)
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
				return (0);
			new->infile = msh->tokens[i + 1]->value;
			new->next = NULL;
			if (!msh->infiles)
				msh->infiles = new;
		}
		i++;
	}
	return (1);
}
