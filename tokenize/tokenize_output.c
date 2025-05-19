#include "../minishell.h"

int	tokenize_output(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	t_outf		*outfiles;
	t_outf		*temp;
	int			count;
	size_t		start;
	
	count = 0;
	start = 0;
	outfiles = malloc(sizeof(t_inf));
	if (!outfiles)
        return (0);
    temp = malloc(sizeof(t_inf));
	if (!temp)
        return (free(outfiles), 0);
	tokens[count++] = make_token(TOKEN_RE_OUTPUT, input, *i, 1);
	(*i)++;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	tokens[count++] = make_token(TOKEN_OUTFILE, input, start, *i - start);
	outfiles->outfile = ft_substr(input, start, *i - start);
	if (!outfiles->outfile)
		return (free(outfiles), free(temp), 0);
	outfiles->next = NULL;
	msh->outfiles = outfiles;
	temp = msh->outfiles;
	while (temp->next)
		temp = temp->next;
	while (outfiles)
	{
		ft_printf("valore di outfiles: %s\n", outfiles->outfile);//////////////////
		outfiles = outfiles->next;
	}
	temp->next = outfiles;
	return (free(temp), count);
}