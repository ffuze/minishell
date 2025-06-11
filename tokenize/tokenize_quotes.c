#include "../minishell.h"

int	tokenize_d_q(t_token **tokens, t_token_enum token_type, \
													char *input, size_t *i)
{
	int		count;
	size_t	start;

	if (input[*i] != '"')
		return (0);
	(*i)++;
	start = *i;
	count = count_tokens(tokens);
	while (input[*i] && input[*i] != '"')
		(*i)++;
	tokens[count++] = make_token(token_type, input, start, *i - start);
	(*i)++;
	return (count);
}

int	tokenize_s_q(t_token **tokens, t_token_enum token_type, \
													char *input, size_t *i)
{
	int		count;
	size_t	start;

	if (input[*i] != '\'')
		return (0);
	(*i)++;
	start = *i;
	count = count_tokens(tokens);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	tokens[count++] = make_token(token_type, input, start, *i - start);
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
		count = tokenize_d_q(tokens, TOKEN_WORD, input, i);
	else if (input[*i] == '\'')
		count = tokenize_s_q(tokens, TOKEN_WORD, input, i);
	return (count);
}
