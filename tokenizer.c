#include "./minishell.h"

t_token	*make_token(t_token_enum token_type, char *input)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = token_type;
	token->value = ft_strdup(input);
	return (token);
}

t_token	**tokenize(char *input, int token_count)
{
	t_token	**tokens;
	int	i;
	int	count;
	int	start;

	tokens = malloc(sizeof(t_token *));
	i = 0;
	count = 0;
	start = 0;
	while (input[i] != '\0')
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '\'')
		{
			start = ++i;
			while (input[i] != '\'')
				i++;
			tokens[count] = make_token(TOKEN_STRING_SINGLE, ft_strlen(input) + start);
			if (input[i] == '\'')
				i++;
		}
		else if (input[i] && input[i] == '"')
		{
			start = ++i;
			while (input[i] != '"')
				i++;
			tokens[count] = make_token(TOKEN_STRING_DOUBLE, ft_strlen(input) + start);
			if (input[i] == '"')
				i++;
		}
		else if (input[i] && input[i] == '$')
		{
			start = ++i;
			while (input[i] != '$')
				i++;
			tokens[count] = make_token(TOKEN_VAR, ft_strlen(input) + start);
		}
		else if (input[i] && input[i] == '|')
		{
			start = ++i;
			
		}
		else
		{
			
		}
	}
}
