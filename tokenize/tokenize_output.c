#include "../minishell.h"

// Check if the fd has got permissions or not
static bool	check_fd(t_msh *msh, t_token *tokens)
{
	int	fd;
	if (!msh || !tokens || tokens->type != TOKEN_OUTFILE)
		return (false);
	fd = open(tokens->value, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_printf("minishell: %s: No such file or directory\n", tokens->value);
		msh->exit_status = 1;
		return (false);
	}
	close(fd);
	unlink(tokens->value);
	return (true);
}

// Check for every command block divided by a pipe that has an output
//  redirection wether the output file exists or not; if it does not,
//  print an error message and skip the whole block until a next pipe is found.
int tokenize_output(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;

	count = count_tokens(tokens);
	msh->outfiles = malloc(sizeof(t_outf));
	msh->outfiles->append_flag = false;
	if (!tokens || !input || !msh)
		return 0;// Se uno dei malloc ha avuto successo la memoria deve essere liberata
	while (input[*i])
	{
		while (input[*i] && input[*i] == ' ')
			(*i)++;
		if (input[*i] == '>' && input[*i + 1] != '>')
		{
			msh->outfiles->append_flag = false;
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
			msh->outfiles->append_flag = true;
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
