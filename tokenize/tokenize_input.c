#include "../minishell.h"

int	tokenize_input(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;
	t_inf	*new_infile;
	t_inf	*temp;

	count = 0;
	start = 0;
	if (!tokens || !input || !msh)
		return (0);
	msh->infiles = NULL;
	tokens[count++] = make_token(TOKEN_RE_INPUT, input, *i, 1);
	(*i)++;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	while (input[*i] && input[*i] != ' ')// ft_isbashprint?
		(*i)++;
	tokens[count++] = make_token(TOKEN_INFILE, input, start, *i - start);
	new_infile = malloc(sizeof(t_inf));
	if (!new_infile)
		return (0);
	new_infile->infile = ft_substr(input, start, *i - start);
	if (!new_infile->infile)
	{
		free(new_infile);
		return (0);
	}
	new_infile->next = NULL;
	if (!msh->infiles)
		msh->infiles = new_infile;
	else
	{
		temp = msh->infiles;
		while (temp->next)
			temp = temp->next;
		temp->next = new_infile;
	}
	//----------------------------------------------------------------_
	t_inf   *current;
	current = msh->infiles;
	while (current)
	{
		ft_printf("valore di infiles: %s\n", current->infile);
		current = current->next;
	}
	//----------------------------------------------------------------_
	// free_infiles(new_infile);// riga 35: msh->infiles = new_infile;
	return (count);
}
