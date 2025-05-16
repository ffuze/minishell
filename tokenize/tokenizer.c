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

void	handle_dollar_sign(t_token **tokens, char *input, int *i)
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
	int i;
	int count;
	size_t	start;
	char	quote;
	char	*clean_token;
	// t_inf	*infiles;

	i = 0;
	start = i;
	tokens = malloc(sizeof(t_token *) * (ft_strlen(input) + 1));
	count = 0;
	clean_token = NULL;
	// infiles = NULL;
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
		else if (input[i] == '<' && input[i + 1] != '<')
		{
			tokens[count++] = make_token(TOKEN_RE_INPUT, input, i, 1);
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			start = i;
			while (input[i] && input[i] != ' ')
				i++;
			tokens[count++] = make_token(TOKEN_INFILE, input, start, i - start);
			if (!msh)
				return (NULL);
			if (!msh->infiles)
			{
				msh->infiles = ft_calloc(1, sizeof(t_inf));
				if (!msh->infiles)
				{
					perror("ft_calloc");
					return (NULL);
				}
			}
			msh->infiles->infile = ft_substr(input, start, i - start);
			if (!msh->infiles->infile)
				return (NULL);
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
// echo "oddio 'no way' sta 'per' funz"i"ona'r'e"
// dovrebbe stampare
// oddio 'no way' sta 'per' funziona'r'e
// ma stampa
// oddio 'no way' sta 'per' funz i ona'r'e
