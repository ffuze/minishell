#include "./minishell.h"

t_token	*make_token(t_token_enum token_type, char *input, size_t start, size_t end)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = token_type;

	token->value = ft_substr(input, start, end);
	return (token);
}

void	handle_single_quotes(t_token *tokens, char *input, int i)
{
	size_t	start;
	size_t	end;
	
	start = 0;
	end = 0;
	start = ++i;
	while (input[i] != '\'')
		i++;
	if (input[i] == '\''){}
		end = ft_strlen(input) - i - start;
	tokens = make_token(TOKEN_STRING_SINGLE, input, start, end);
}

void	handle_double_quotes(t_token *tokens, char *input, int i)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	start = ++i;
	while (input[i] != '\'')
		i++;
	if (input[i] == '\''){}
		end = ft_strlen(input) - i - start;
	tokens = make_token(TOKEN_STRING_SINGLE, input, start, end);
}

void	handle_dollar_sign(t_token *tokens, char *input, int i)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	start = ++i;
	while (input[i] != '$')
		i++;
	tokens = make_token(TOKEN_VAR, input, start, ft_strlen(input) - 1);
}

void	handle_no_quotes(t_token *tokens, char *input, int i)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '\''
		&& input[i] != '"' && input[i] != '|' && input[i] != '$')
		i++;
	if (input[i] == '"')
		end = ft_strlen(input) - i - start;
	tokens = make_token(TOKEN_WORD, input, start, end);
}

t_token	**tokenize(char *input, int token_count)
{
	t_token	**tokens;
	int		i;
	int		count;

	tokens = malloc(sizeof(t_token *));
	i = 0;
	count = 0;
	while (input[i] != '\0')
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '\'')
			handle_single_quotes(tokens[count], input, i);
		else if (input[i] && input[i] == '"')
			handle_double_quotes(tokens[count], input, i);
		else if (input[i] && input[i] == '$')
			handle_dollar_sign(tokens[count], input, i);
		else if (input[i] && input[i] == '|')
		{
			tokens[count] = make_token(TOKEN_PIPE, input, i, 1);
			i++;
		}
		else
			handle_no_quotes(tokens[count], input, i);
	}
}
