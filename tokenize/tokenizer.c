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

t_token **tokenize(t_msh *msh, char *input)
{
	t_token	**tokens;
	size_t	i;
	int		count;
	size_t	start;
	// char	*msh->cl_input;

	i = 0;
	start = i;
	count = 0;
	msh->outfi_flag = false;
	msh->pipe_count = 0;
	msh->cl_input = ft_remove_quotes(msh, input);
	if (!msh->cl_input)
		return (NULL);
	tokens = ft_calloc((count_args(input) + 1), sizeof(t_token *));
	if (!tokens)
		return (free(msh->cl_input), NULL);
	while (msh->cl_input[i])
	{
		while (msh->cl_input[i] == ' ')
			i++;
		if (!msh->cl_input[i])
			break;
		else if (msh->cl_input[i] == '|')
		{
			tokens[count++] = make_token(TOKEN_PIPE, msh->cl_input, i, 1);
			i++;
			msh->pipe_count++;
		}
		else if (msh->cl_input[i] == '<')// TOKEN_RE_INPUT
			count += tokenize_input(msh, tokens, msh->cl_input, &i);
		else if (msh->cl_input[i] == '>')// TOKEN_RE_OUTPUT
		{
			msh->outfi_flag = true;
			count = tokenize_output(msh, tokens, msh->cl_input, &i);
		}
		else
		{
			start = i;
			while (msh->cl_input[i] && msh->cl_input[i] != ' '/*  && input[i] != '\'' && input[i] != '"' */)
				i++;
			tokens[count++] = make_token(TOKEN_WORD, msh->cl_input, start, i - start);
		}
		// tokenize_commands(msh);
	}
	tokens[count] = NULL;
	free(msh->cl_input);
	return (tokens);
}
// echo "oddio 'no way' sta 'per' funz"i"ona'r'e"
// dovrebbe stampare
// oddio 'no way' sta 'per' funziona'r'e
// ma stampa
// oddio 'no way' sta 'per' funz i ona'r'e
