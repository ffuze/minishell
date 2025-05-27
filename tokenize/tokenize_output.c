#include "../minishell.h"

static int	count_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
		i++;
	return (i);
}

int	tokenize_output(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count = 0;
	size_t	start = 0;
	t_outf	*new_outfile;
	t_outf	*temp;
	t_outf	*current;

	if (!tokens || !input || !msh)
		return 0;
	count = count_tokens(tokens);
	msh->outfiles = NULL;
	new_outfile = malloc(sizeof(t_outf));
	if (!new_outfile)
		return 0;
	if (input[*i + 1] != '>')
	{
		tokens[count++] = make_token(TOKEN_RE_OUTPUT, input, *i, 1);
		(*i)++;
		new_outfile->append_flag = false;
	}
	else if (input[*i + 1] == '>')
	{
		tokens[count++] = make_token(TOKEN_RE_OUTPUT, input, *i, 2);
		(*i) += 2;
		new_outfile->append_flag = true;
	}
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	tokens[count++] = make_token(TOKEN_OUTFILE, input, start, *i - start);
	
	new_outfile->outfile = ft_substr(input, start, *i - start);
	if (!new_outfile->outfile)
	{
		free(new_outfile);
		return 0;
	}
	new_outfile->next = NULL;
	if (!msh->outfiles)
		msh->outfiles = new_outfile;
	else
	{
		temp = msh->outfiles;
		while (temp->next)
			temp = temp->next;
		temp->next = new_outfile;
	}
	current = msh->outfiles;
	while (current)
	{
		ft_printf("valore di outfiles: %s\n", current->outfile);
		current = current->next;
	}
	return (count);
}

/* {
	t_outf		*outfiles;
	t_outf		*temp;
	int			count;
	size_t		start;
	
	count = 0;
	start = 0;
	outfiles = malloc(sizeof(t_outf));
	if (!outfiles)
		return (0);
	temp = malloc(sizeof(t_outf));
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
} */
