#include "../minishell.h"

// Reversed ft_split(): joins all strings in the array str_segment.
//  Returns a single string or NULL on failure.
char	*join_multistr(char **str_segment)
{
	char	*joined_strs;
	int		i;

	joined_strs = ft_calloc(1, 1);
	i = 0;
	while (str_segment[i])
	{
		joined_strs = ft_strjoin2(joined_strs, str_segment[i]);
		if (!joined_strs)
			return (NULL);
		i++;
	}
	return (joined_strs);
}

static char	*handle_quotes(char *input, size_t *i, char *word)
{
	size_t	start;
	char	*str_segment;

	start = *i + 1;
	if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
			(*i)++;
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
	}
	str_segment = ft_substr(input, start, *i - start);
	if (!str_segment)
		return (NULL);
	word = ft_strjoin2(word, str_segment);
	free(str_segment);
	if (!word)
		return (NULL);
	return (word);
}

int		tokenize_word(t_token **tokens, char *input, size_t *i, int *count)
{
	size_t	start;
	char	*str_segment;
	char	*word;

	start = *i;
	word = ft_calloc(1, 1);
	while (input[*i] && input[*i] != ' ' && !ft_isoperator(input[*i]))
	{
		start = *i;
		while (input[*i] && input[*i] != ' ' && !ft_isoperator(input[*i]) && \
										input[*i] != '\'' && input[*i] != '"')
			(*i)++;
		str_segment = ft_substr(input, start, *i - start);
		word = ft_strjoin2(word, str_segment);
		free(str_segment);
		if (input[*i] == '\'' || input[*i] == '"')
			word = handle_quotes(input, i, word);
		if (input[*i] == '"' || input[*i] == '\'')
			(*i)++;
	}
	tokens[(*count)++] = make_token(TOKEN_WORD, word, 0, ft_strlen(word));
	return (free(word), 1);
}

/* int	tokenize_d_q(t_token **tokens, t_token_enum token_type, \
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
	//--------------------------------------------------------
	char	next_quote;
	next_quote = '\0';
	if (input[*i] == '"' || input[*i] == '\'')// Bisogna rimovere la quote intermedia
	{
		next_quote = input[*i];
		while (input[*i] && input[*i] != next_quote)
			i++;
	}
	//--------------------------------------------------------
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
} */
