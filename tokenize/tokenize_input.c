#include "../minishell.h"

int	tokenize_input(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	t_inf		*infiles;
	t_inf		*temp;
	int			count;
	size_t		start;
	
	count = 0;
	start = 0;
	infiles = malloc(sizeof(t_inf));
	if (!infiles)
        return (0);
    temp = malloc(sizeof(t_inf));
	if (!temp)
        return (free(infiles), 0);
	tokens[count++] = make_token(TOKEN_RE_INPUT, input, *i, 1);
	(*i)++;
	while (input[*i] && input[*i] == ' ')
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	tokens[count++] = make_token(TOKEN_INFILE, input, start, *i - start);
	infiles->infile = ft_substr(input, start, *i - start);
	if (!infiles->infile)
		return (free(infiles), free(temp), 0);
	infiles->next = NULL;
	msh->infiles = infiles;
	temp = msh->infiles;
	while (temp->next)
		temp = temp->next;
	while (infiles)
	{
		ft_printf("valore di infiles: %s\n", infiles->infile);//////////////////
		infiles = infiles->next;
	}
	temp->next = infiles;
	return (free(temp), count);
}