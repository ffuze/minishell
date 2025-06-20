#include "../minishell.h"

// Check if the fd has got permissions or not
static bool	check_fd(t_msh *msh, t_token *tokens)
{
	int	fd;
	if (!msh || !tokens || tokens->type != TOKEN_INFILE || !tokens->value)
		return (false);
	if (ft_strcmp(tokens->value, "") == 0)
	{
		ft_printfd(2, \
			RED"norminette: syntax error near unexpected token `newline'\n" \
			NO_ALL, tokens->value);
		return (false);
	}
	fd = open(tokens->value, O_RDONLY);
	if (fd < 0)
	{
		ft_printfd(2, RED"minishell: %s: No such file or directory\n"NO_ALL, \
																tokens->value);
		msh->exit_status = 1;
		return (false);
	}
	close(fd);
	return (true);
}

// Check for every command block divided by a pipe that has an
//  input redirection wether the input file exists or not; if it does not,
//  print an error message and skip the wholeblock until a next pipe is found.
int tokenize_input(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;
	
	count = 0;
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
	return (count);
}

// Check if all input files exist or not in order to avoid
// potential invalid accesses 
int validate_input_files(t_msh *msh)
{
	int i;
	
	i = 0;
	if (!msh->tokens)
		return (0);
	while (msh->tokens[i])
	{
		if (msh->tokens[i]->type == TOKEN_INFILE)
		{
			if (!check_fd(msh, msh->tokens[i]))
				return (0);
		}
		i++;
	}
	return (1);
}