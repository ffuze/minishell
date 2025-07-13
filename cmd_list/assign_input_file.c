
#include "../minishell.h"

static bool	check_token_value(t_token *token, t_cmds *new_node)
{
	if (token->type == TOKEN_INFILE)
	{
		if (!check_fd_in(token))
		{
			new_node->abort_flag = true;
			return (false);
		}
	}
	else if (token->type == TOKEN_LIMITER)
	{
		if (!token->value || !token->value[0])
		{
			new_node->abort_flag = true;
			print_err("Minishell:", \
						"syntax error found in heredoc redirection.\n");
			return (false);
		}
	}
	return (true);
}

static char	*get_readline_result(const char *prompt)
{
	char	*readline_result;

	readline_result = readline(prompt);
	if (!readline_result)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}
	return (ft_strjoin2(readline_result, "\n"));
}

static int	rl_cycle(t_msh *msh, t_cmds *new_node, int heredoc_fd, char *str)
{
	str = get_readline_result("> ");
	if (g_sigint_rec)
	{
		new_node->abort_flag = 1;
		msh->exit_status = 130;
		g_sigint_rec = 0;
		return (free(str), close(heredoc_fd), unlink(new_node->infile), 0);
	}
	str = ft_expanded_heredoc_cpy(msh, str);
	if (!str)
	{
		ft_printfd(2, RED"pokeshell: warning: heredoc delimited by ");
		ft_printfd(2, "end-of-file (wanted `%s')\n"NO_ALL, new_node->limiter);
		return (close(heredoc_fd), 0);
	}
	if (ft_strcmp(new_node->limiter, str) == 0)
	{
		free(str);
		reset_child_signals();
		return (close(heredoc_fd), 0);
	}
	ft_printfd(heredoc_fd, "%s", str);
	free(str);
	return (1);
}

static int	generate_heredoc(t_msh *msh, t_token **tokens, int *j,
	t_cmds *new_node)
{
	int		heredoc_fd;
	char	*str;

	str = NULL;
	new_node->heredoc_flag = true;
	new_node->limiter = ft_strjoin(tokens[*j]->value, "\n");
	new_node->infile = ft_strjoin2(ft_itoa(*j), "heredoc.txt");
	heredoc_fd = open(new_node->infile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	setup_signals_heredoc();
	ft_printf(BLUE"global: %d\n"NO_ALL, g_sigint_rec);
	while (rl_cycle(msh, new_node, heredoc_fd, str) > 0)
	{
		;
	}
	return (close(heredoc_fd), 0);
}

// Assigns to the relative command list node the name of the 
//  input redirection file. Sets it to NULL if there is none.
// If a heredoc is to be created, it will be named *token number*heredoc.txt.
void	assign_infile_value(t_msh *msh, t_token **tokens, int *j, \
															t_cmds *new_node)
{
	new_node->infile = NULL;
	new_node->heredoc_flag = false;
	new_node->limiter = NULL;
	while (*j > 0 && tokens[*j - 1]->type != TOKEN_PIPE)
		(*j)--;
	while (tokens[*j] && tokens[*j]->type != TOKEN_PIPE)
	{
		if (tokens[*j]->type == TOKEN_INFILE)
		{
			if (!check_token_value(tokens[*j], new_node))
				return ;
			free_input_redirection(new_node);
			new_node->infile = ft_strdup(tokens[*j]->value);
		}
		else if (tokens[*j]->type == TOKEN_LIMITER)
		{
			if (!check_token_value(tokens[*j], new_node))
				return ;
			free_input_redirection(new_node);
			generate_heredoc(msh, tokens, j, new_node);
		}
		(*j)++;
	}
}
