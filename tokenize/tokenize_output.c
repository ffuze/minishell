#include "../minishell.h"

// Check if the fd has got permissions or not
static bool	check_fd(t_msh *msh, t_token *tokens)
{
	int	fd;
	if (!msh || !tokens || tokens->type != TOKEN_OUTFILE)
		return (false);
	fd = open(tokens->value, O_WRONLY, O_CREAT, 0644);
	if (fd < 0)
	{
		ft_printf("minishell: %s: Permission denied\n", tokens->value);
		msh->exit_status = 1;
		return (false);
	}
	close(fd);
	return (true);
}

// Check for every command block divided by a pipe that has an output redirection wether
// the output file exists or not; if it does not, print an error message and skip the whole
// block until a next pipe is found
int tokenize_output(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;
	
	count = 0;
	if (!tokens || !input || !msh)
		return 0;
	while (input[*i])
	{
		while (input[*i] && input[*i] == ' ')
			(*i)++;
		if (input[*i] == '>' && input[*i + 1] != '>')
		{
			tokens[count++] = make_token(TOKEN_RE_OUTPUT, input, *i, 1);
			(*i)++;
			while (input[*i] && input[*i] == ' ')
				(*i)++;
			start = *i;
			while (input[*i] && input[*i] != ' ' && input[*i] != '|') // ft_isbashprint ?
				(*i)++;
			tokens[count++] = make_token(TOKEN_OUTFILE, input, start, *i - start);
		}
		else if (input[*i] == '>' && input[*i + 1] == '>')
		{
			tokens[count++] = make_token(TOKEN_RE_OUTPUT, input, *i, 2);
			(*i) += 2;
			while (input[*i] && input[*i] == ' ')
				(*i)++;
			start = *i;
			while (input[*i] && input[*i] != ' ' && input[*i] != '|') // ft_isbashprint ?
				(*i)++;
			tokens[count++] = make_token(TOKEN_OUTFILE, input, start, *i - start);
		}
		if (!check_fd(msh, tokens[count - 1]))
		{
			free(tokens);
			while (input[*i] && input[*i] != '|')
				(*i)++;
			if (input[*i] == '|')
				(*i)++;
			return (0);
		}
	}
	return (count);
}
