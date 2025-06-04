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
	char	*clean_input;

	i = 0;
	start = i;
	count = 0;
	msh->outfi_flag = false;
	msh->pipe_count = 0;
	clean_input = ft_remove_quotes(msh->envp2, input);
	// printf(BLUE"N words: %zu\n"NO_ALL, count_args(input));///////////////////////////////////
	if (!clean_input)
		return (NULL);
	tokens = ft_calloc((count_args(input) + 1), sizeof(t_token *));// ft_calloc(count_words(clean_input) + 1, sizeof(t_token *));
	if (!tokens)
		return (free(clean_input), NULL);
	while (clean_input[i])
	{
		while (clean_input[i] == ' ')
			i++;
		if (!clean_input[i])
			break;
		else if (clean_input[i] == '|')
		{
			tokens[count++] = make_token(TOKEN_PIPE, clean_input, i, 1);
			i++;
			msh->pipe_count++;
		}
		else if (clean_input[i] == '<')// TOKEN_RE_INPUT
			count += tokenize_input(msh, tokens, clean_input, &i);
		else if (input[i] == '>')// TOKEN_RE_OUTPUT
		{
			msh->outfi_flag = true;
			count = tokenize_output(msh, tokens, clean_input, &i);
		}
		else if (clean_input[i] == '$')// TOKEN_VAR da spostare in ft_remove_quotes()
			count += tokenize_env_var(msh, tokens, clean_input, &i);
		else
		{
			start = i;
			while (clean_input[i] && clean_input[i] != ' '/*  && input[i] != '\'' && input[i] != '"' */)
				i++;
			tokens[count++] = make_token(TOKEN_WORD, clean_input, start, i - start);
		}
		// tokenize_commands(msh);
	}
	tokens[count] = NULL;
	free(clean_input);
	return (tokens);
}
// echo "oddio 'no way' sta 'per' funz"i"ona'r'e"
// dovrebbe stampare
// oddio 'no way' sta 'per' funziona'r'e
// ma stampa
// oddio 'no way' sta 'per' funz i ona'r'e
