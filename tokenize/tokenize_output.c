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

	if (!tokens || !input || !msh)
		return (0);
	count = count_tokens(tokens);
	msh->outfiles = NULL;
	new_outfile = malloc(sizeof(t_outf));
	if (!new_outfile)
		return (count_tokens(tokens));
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
	while (input[*i] && input[*i] != ' ')// ft_isbashprint?
		(*i)++;
	tokens[count++] = make_token(TOKEN_OUTFILE, input, start, *i - start);
	new_outfile->outfile = ft_substr(input, start, *i - start);
	if (!new_outfile->outfile)
		return (free(new_outfile), count_tokens(tokens));
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
	//----------------------------------------------------------------_
	t_outf	*current;
	current = msh->outfiles;
	while (current)
	{
		ft_printf("Valore di outfiles: %s. Append_flag: %d\n", current->outfile, current->append_flag);
		current = current->next;
	}
	//----------------------------------------------------------------_
	return (count);
}
