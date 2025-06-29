#include "../minishell.h"

// Check for every command block divided by a pipe that has an
//  input redirection wether the input file exists or not; if it does not,
//  print an error message and skip the wholeblock until a next pipe is found.
int tokenize_input(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;
	int		starting_count;
	
	starting_count = count_tokens(tokens);
	count = starting_count;
	if (!tokens || !input || !msh)
		return (0);
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	if (input[*i] == '<' && input[*i + 1] != '<')
	{
		tokens[count++] = make_token(TOKEN_RE_INPUT, input, *i, 1);
		(*i)++;
		while (input[*i] && input[*i] == ' ')
			(*i)++;
		start = *i;
		while (input[*i] && input[*i] != ' ' && input[*i] != '|')
			(*i)++;
		tokens[count++] = make_token(TOKEN_INFILE, input, start, *i - start);		
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		tokens[count++] = make_token(TOKEN_RE_INPUT, input, *i, 2);
		(*i) += 2;
		while (input[*i] && input[*i] == ' ')
			(*i)++;
		start = *i;
		while (input[*i] && input[*i] != ' ' && input[*i] != '|')
			(*i)++;
		tokens[count++] = make_token(TOKEN_LIMITER, input, start, *i - start);	
	}
	return (count - starting_count);
}
