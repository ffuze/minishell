#include "./minishell.h"

t_token	*make_token(t_token_enum token_type, char *input, size_t start, \
																size_t end)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = token_type;
	token->value = ft_substr(input, start, end);
	return (token);
}
	
// void	handle_single_quotes(t_token **tokens, char *input, int *i, int count)
// {
// 	size_t	start;
// 	size_t	end;
// 	char	*tmp;

// 	tmp = NULL;
// 	start = 0;
// 	end = 0;
// 	start = ++(*i);
// 	while (input[*i] && input[*i] != '\'')
// 		(*i)++;
// 	if (input[*i] == '\'')
// 		end = *i - start;
// 	*tokens = make_token(TOKEN_WORD, input, start, end);
// 	(*i)++;
// 	if (input[*i] != '\0' && ft_isbashprint(input[*i]))
// 	{
// 		start = *i;
// 		while (input[*i] && ft_isbashprint(input[*i]))
// 			(*i)++;
// 		end = (*i) - start - 1;
// 		tmp = ft_substr(input, start, end);
// 		tokens[count]->value = ft_strjoin(tmp, tokens[count]->value);
// 		free(tmp);
// 	}
// 	// (*i)++;
// }

// void	handle_double_quotes(t_token **tokens, char *input, int *i)
// {
// 	size_t	start;
// 	size_t	end;

// 	start = 0;
// 	end = 0;
// 	start = ++(*i);
// 	while (input[*i] != '"')
// 		(*i)++;
// 	if (input[*i] == '"')
// 		end = *i - start;
// 	*tokens = make_token(TOKEN_WORD, input, start, end);
// 	(*i)++;
// }

int	count_quotes(char *input, int quote_type)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
			sq++;
		else if (input[i] == '"')
			dq++;
		i++;
	}
	if (!quote_type)
		return (sq);
	return (dq);
}

void handle_word_block(t_token **tokens, char *input, int *i, int count)
{
	int 	start;
	int		singleq;
	int		doubleq;

	start = *i;
	singleq = 0;
	doubleq = 0;
	while (input[*i])
	{
		if (input[*i] == '\'')
		{
			while (input[++(*i)] != '\'' && input[*i] != '\0')
				;
			if (input[*i] == '\'')
				(*i)++;
		}
		else if (input[*i] == '"')
		{
			while (input[++(*i)] != '"' && input[*i] != '\0')
				;
			if (input[*i] == '"')
				(*i)++;
		}
	}
	tokens[count] = make_token(TOKEN_WORD, input, start, *i - start);
}

void	handle_dollar_sign(t_token **tokens, char *input, int *i)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	start = ++(*i);
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	*tokens = make_token(TOKEN_VAR, input, start, ft_strlen(input) - 1);
	(*i)++;
}

// void	handle_no_quotes(t_token **tokens, char *input, int *i)
// {
// 	size_t	start;
// 	size_t	end;

// 	start = 0;
// 	end = 0;
// 	start = *i;
// 	while (input[*i] && input[*i] != ' ' && input[*i] != '\''
// 		&& input[*i] != '"' && input[*i] != '|' && input[*i] != '$')
// 		(*i)++;
// 	if (!input[*i] || input[*i] == ' ')
// 		end = *i - start;
// 	else
// 		return ;
// 	*tokens = make_token(TOKEN_WORD, input, start, end);
// 	(*i)++;
// }

t_token **tokenize(char *input)
{
	t_token **tokens;
	int i;
	int count;

	tokens = malloc(sizeof(t_token *) * (ft_strlen(input) + 1)); // spazio extra
	count = 0;
	i = 0;
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (!input[i])
			break;
		if (input[i] == '|')
		{
			tokens[count] = make_token(TOKEN_PIPE, input, i, 1);
			i++;
		}
		else if (input[i] == '$')
			handle_dollar_sign(tokens, input, &i);
		else
			handle_word_block(tokens, input, &i, count);
		count++;
	}
	tokens[count] = NULL;
	return (tokens);
}
