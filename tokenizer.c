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
	
void	handle_single_quotes(t_token **tokens, char *input, int *i, int count)
{
	size_t	start;
	size_t	end;
	char	*tmp;

	tmp = NULL;
	start = 0;
	end = 0;
	start = ++(*i);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] == '\'')
		end = *i - start;
	*tokens = make_token(TOKEN_WORD, input, start, end);
	(*i)++;
	if (input[*i] != '\0' && ft_isbashprint(input[*i]))
	{
		start = *i;
		while (input[*i] && ft_isbashprint(input[*i]))
			(*i)++;
		end = (*i) - start - 1;
		tmp = ft_substr(input, start, end);
		tokens[count]->value = ft_strjoin(tmp, tokens[count]->value);
		free(tmp);
	}
	// (*i)++;
}

void	handle_double_quotes(t_token **tokens, char *input, int *i)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	start = ++(*i);
	while (input[*i] != '"')
		(*i)++;
	if (input[*i] == '"')
		end = *i - start;
	*tokens = make_token(TOKEN_WORD, input, start, end);
	(*i)++;
}

void	handle_dollar_sign(t_token **tokens, char *input, int *i)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	start = ++(*i);
	while (input[*i] != '$')
		(*i)++;
	*tokens = make_token(TOKEN_VAR, input, start, ft_strlen(input) - 1);
	(*i)++;
}

void	handle_no_quotes(t_token **tokens, char *input, int *i)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\''
		&& input[*i] != '"' && input[*i] != '|' && input[*i] != '$')
		(*i)++;
	if (!input[*i] || input[*i] == ' ')
		end = *i - start;
	else
		return ;
	*tokens = make_token(TOKEN_WORD, input, start, end);
	(*i)++;
}

t_token	**tokenize(char *input)
{
	t_token	**tokens;
	int		i;
	int		count;
	char	*main_tmp;

	tokens = malloc(sizeof(t_token) * (ft_strlen(input) + 1));
	i = 0;
	count = 0;
	main_tmp = NULL;
	while (input[i] != '\0')
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '\'')
			handle_single_quotes(&tokens[count], input, &i, count);
		else if (input[i] && input[i] == '"')
			handle_double_quotes(&tokens[count], input, &i);
		else if (input[i] && input[i] == '$')
			handle_dollar_sign(&tokens[count], input, &i);
		else if (input[i] && input[i] == '|')
		{
			tokens[count] = make_token(TOKEN_PIPE, input, i, 1);
			i++;
		}
		else if (input[i] && input[i] != ' ')
			handle_no_quotes(&tokens[count], input, &i);
		count++;
	}
	tokens[count] = NULL;
	return (tokens);
}
