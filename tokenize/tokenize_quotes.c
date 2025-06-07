#include "../minishell.h"


static int	tokenize_d_q(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;

	(*i)++;
	start = i;
	count = count_tokens(tokens);
	while (input[*i] && input[*i] != '"')
		i++;
	tokens[count++] = make_token(TOKEN_WORD, input, start, i - start);
	return (count);
}

static int	tokenize_s_q(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int	count;

	count = count_tokens(tokens);
	return (count);
}

int	tokenize_quotes(t_msh *msh, t_token **tokens, char *input, int *i)
{
	int	count;

	count = 0;
	if (input[*i] == '"')
		count = tokenize_d_q(msh, tokens, input, &i);// &(*i)++ ?
	else if ((input[*i] == '\''))
		count = tokenize_s_q(msh, tokens, input, &i);
	return (count);
}