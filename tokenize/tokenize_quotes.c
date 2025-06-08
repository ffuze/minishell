#include "../minishell.h"

static int	tokenize_d_q(t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;

	(*i)++;
	start = *i;
	count = count_tokens(tokens);
	while (input[*i] && input[*i] != '"')
		(*i)++;
	tokens[count++] = make_token(TOKEN_WORD, input, start, *i - start);
	(*i)++;
	return (count);
}

static int	tokenize_s_q(t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;

	(*i)++;
	start = *i;
	count = count_tokens(tokens);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	tokens[count++] = make_token(TOKEN_WORD, input, start, *i - start);
	(*i)++;
	return (count);
}

// Sets a token for the substring between quotes,
//  then returns the current number of tokens.
int	tokenize_quotes(t_token **tokens, char *input, size_t *i)
{
	int	count;

	count = 0;
	if (input[*i] == '"')
		count = tokenize_d_q(tokens, input, i);// &(*i)++ ?
	else if (input[*i] == '\'')
		count = tokenize_s_q(tokens, input, i);
	return (count);
}
