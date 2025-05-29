#include "../minishell.h"

// Insert the input file into the infiles linked list
// Create a token for each input file name found
int tokenize_input(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int     count;
	size_t  start;

	count = 0;
	if (!tokens || !input || !msh)
		return (0);
	msh->infiles = NULL;
	tokens[count] = make_token(TOKEN_RE_INPUT, input, *i, 1);
	if (!tokens[count])
		return (0);
	count++;
	(*i)++;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	tokens[count] = make_token(TOKEN_INFILE, input, start, *i - start);
	if (!tokens[count])
		return (0);
	count++;
	return (count);
}

int insert_input(t_msh *msh, t_token **tokens, size_t *i)
{
	t_inf   *new_infile;
	int     count;

	count = tokenize_input(msh, tokens, tokens[0]->value, &tokens[0]->value);
	if (count <= 0)
		return (0);
	new_infile = malloc(sizeof(t_inf));
	if (!new_infile)
		return (0);
	new_infile->infile = tokens[count - 1]->value;
	new_infile->next = NULL;
	if (!msh->infiles)
		msh->infiles = new_infile;
	else
	{
		t_inf *temp = msh->infiles;
		while (temp->next)
			temp = temp->next;
		temp->next = new_infile;
	}
	t_inf *current = msh->infiles;
	while (current)
	{
		ft_printf("valore di infiles: %s\n", current->infile);
		current = current->next;
	}
	return (count);
}

