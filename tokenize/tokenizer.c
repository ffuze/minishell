#include "../minishell.h"

t_token **tokenize(t_msh *msh, char *input)
{
	t_token	**tokens;
	size_t	i;
	int		count;
	size_t	start;

	i = 0;
	start = i;
	count = 0;
	msh->outfi_flag = false;
	msh->pipe_count = 0;
	msh->exp_input = ft_parse_and_expand(msh, input);
	if (!msh->exp_input)
		return (NULL);
	tokens = ft_calloc((count_args(input) + 1), sizeof(t_token *));
	if (!tokens)
		return (free(msh->exp_input), NULL);
	while (msh->exp_input[i])
	{
		while (msh->exp_input[i] == ' ')
			i++;
		if (!msh->exp_input[i])
			break;
		else if (msh->exp_input[i] == '|')
		{
			tokens[count++] = make_token(TOKEN_PIPE, msh->exp_input, i, 1);
			i++;
			msh->pipe_count++;
		}
		else if (msh->exp_input[i] == '<')// TOKEN_RE_INPUT
			count += tokenize_input(msh, tokens, msh->exp_input, &i);
		else if (msh->exp_input[i] == '>')// TOKEN_RE_OUTPUT
		{
			msh->outfi_flag = true;
			count = tokenize_output(msh, tokens, msh->exp_input, &i);
		}
		// else if (msh->exp_input[i] == '"' || msh->exp_input[i] == '\'')// QUOTES
		// 	count = tokenize_quotes(msh, tokens, msh->exp_input, &i);
		else
		{
			start = i;
			while (msh->exp_input[i] && msh->exp_input[i] != ' '/*  && input[i] != '\'' && input[i] != '"' */)
				i++;
			tokens[count++] = make_token(TOKEN_WORD, msh->exp_input, start, i - start);
		}
		// tokenize_commands(msh);
	}
	tokens[count] = NULL;
	free(msh->exp_input);
	return (tokens);
}
// echo "oddio 'no way' sta 'per' funz"i"ona'r'e"
// dovrebbe stampare
// oddio 'no way' sta 'per' funziona'r'e
// ma stampa
// oddio 'no way' sta 'per' funz i ona'r'e
