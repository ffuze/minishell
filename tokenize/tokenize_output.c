#include "../minishell.h"

// Destroys the file if the fd has got permissions and the redirection
// is in append mode.
static void	reset_fd(t_msh *msh, t_token **tokens, int count)
{
	int	fd;
	if (!msh || !tokens[count] || tokens[count]->type != TOKEN_OUTFILE)
		return ;
	fd = open(tokens[count]->value, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return ;
	close(fd);
	return ;
}

// Tokenizes the single redirection in output (>).
static void	single_redirect(t_token **tokens, char *input, size_t *i, \
																int *count)
{
	size_t	start;

	tokens[(*count)++] = make_token(TOKEN_RE_OUTPUT, input, *i, 1);
	(*i)++;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '|')
		return ;
	while (input[*i] && input[*i] != ' ' && !ft_isoperator(input[*i]))
		(*i)++;
	tokens[(*count)++] = make_token(TOKEN_OUTFILE, input, start, *i - start);
}

// Tokenizes the double redirection in output (>>).
static void	double_redirect(t_token **tokens, char *input, size_t *i, \
																int *count)
{
	size_t	start;

	tokens[(*count)++] = make_token(TOKEN_RE_OUTPUT, input, *i, 2);
	(*i) += 2;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '|')
		return ;
	while (input[*i] && input[*i] != ' ' && !ft_isoperator(input[*i]))
		(*i)++;
	tokens[(*count)++] = make_token(TOKEN_OUTFILE, input, start, *i - start);
}

// Check for every command block divided by a pipe that has an output
//  redirection wether the output file exists or not; if it does not,
//  print an error message and skip the whole block until a next pipe is found.
int tokenize_output(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		starting_count;
	int		count;

	starting_count = count_tokens(tokens);
	count = starting_count;
	if (!tokens || !input || !msh)
		return (0);
	while (input[*i] && (input[*i] == ' ' || input[*i] == '>'))
	{
		while (input[*i] && input[*i] == ' ')
			(*i)++;
		if (input[*i] == '>' && (!input[*i + 1] || input[*i + 1] != '>'))
			single_redirect(tokens, input, i, &count);
		else if (input[*i] == '>' && input[*i + 1] == '>')
			double_redirect(tokens, input, i, &count);
		reset_fd(msh, tokens, count - 1);
	}
	return (count);
}
