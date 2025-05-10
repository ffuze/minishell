#include "./minishell.h"

t_token	*make_token(t_token_enum token_type, char *input, size_t start, \
																size_t end)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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

char	*remove_outer_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\'')))
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

void	handle_word_block(t_token **tokens, int count)
{
	char *cleaned;

	cleaned = remove_outer_quotes(tokens[count]->value);
	free(tokens[count]->value);
	tokens[count++]->value = cleaned;
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
	size_t	start;
	char	quote;
	char	*clean_token;

	i = 0;
	start = i;
	tokens = malloc(sizeof(t_token *) * (ft_strlen(input) + 1)); // spazio extra
	count = 0;
	clean_token = NULL;
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
			tokens[count++] = make_token(TOKEN_PIPE, input, i, 1);
			i++;
		}
		else if (input[i] == '<')
		{
			tokens[count++] = make_token(TOKEN_RE_INPUT, input, i, 1);
			i++;
		}
		else if (input[i] == '>')
		{
			tokens[count++] = make_token(TOKEN_RE_OUTPUT, input, i, 1);
			i++;
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			start = i;
			while (input[i] && input[i] != quote)
				i++;
			tokens[count] = make_token(TOKEN_WORD, input, start, i - start);
			clean_token = remove_outer_quotes(tokens[count]->value);
			free(tokens[count]->value);
			tokens[count]->value = clean_token;
			count++;
			i++;
		}
		else if (input[i] == '$')
			handle_dollar_sign(tokens, input, &i);
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '\'' && input[i] != '"')
				i++;
			tokens[count++] = make_token(TOKEN_WORD, input, start, i - start);
		}
	}
	tokens[count] = NULL;
	return (tokens);
}
