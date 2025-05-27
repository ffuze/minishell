#include "../minishell.h"

t_token	*make_token(t_token_enum token_type, char *input, size_t start, \
																size_t end)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->value = ft_substr(input, start, end);
    if (!token->value)
    {
        free(token);
        return (NULL);
    }
	return (token);
}

char	*remove_outer_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"'
		&& str[1] == '\'' && str[len - 2] == '\'')
        || (str[0] == '\'' && str[len - 1] == '\''
		&& str[1] == '"' && str[len - 2] == '"')))
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

void	handle_dollar_sign(t_token **tokens, char *input, size_t *i)
{
	size_t	start;
	// size_t	end;

	start = 0;
	// end = 0;
	start = ++(*i);
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	*tokens = make_token(TOKEN_VAR, input, start, ft_strlen(input) - 1);
	(*i)++;
}

t_token **tokenize(t_msh *msh, char *input)
{
	t_token **tokens;
	size_t i;
	int count;
	size_t	start;
	char	quote;
	char	*clean_token;

	i = 0;
	start = i;
	tokens = ft_calloc((ft_strlen(input) + 1), sizeof(t_token *));
	count = 0;
	clean_token = NULL;
	msh->pipe_count = 0;
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
			msh->pipe_count++;
		}
		else if (input[i] == '<' && input[i + 1] != '<')
            count += tokenize_input(msh, tokens, input, &i);
        else if (input[i] == '<' && input[i + 1] == '<')
        {
            tokens[count++] = make_token(TOKEN_RE_INPUT, input, i, 2);
            i += 2;
        }
		else if (input[i] == '>' && input[i + 1] != '>')
		{ 
			tokens[count++] = make_token(TOKEN_RE_OUTPUT, input, i, 1);
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			start = i;
			while (input[i] && input[i] != ' ')
				i++;
			tokens[count++] = make_token(TOKEN_OUTFILE, input, start, i - start);
			msh->outfiles = (t_outf *)ft_substr(input, start, i - start);
		}
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            tokens[count++] = make_token(TOKEN_RE_OUTPUT, input, i, 2);
            i += 2;
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
	// tokenize_commands(msh);
    tokens[count] = NULL;
	return (tokens);
}
// echo "oddio 'no way' sta 'per' funz"i"ona'r'e"
// dovrebbe stampare
// oddio 'no way' sta 'per' funziona'r'e
// ma stampa
// oddio 'no way' sta 'per' funz i ona'r'e
