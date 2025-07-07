/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alek <alek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:54:02 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/07 03:46:48 by alek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks the file descriptor's permissions.
static bool	check_fd(t_token *token)
{
	int	fd;

	if (!token->value || !token->value[0])
	{
		ft_printfd(2, \
			RED"minishell: syntax error found in input redirection\n" \
			NO_ALL);
		return (0);
	}
	fd = access(token->value, F_OK | R_OK);
	if (fd < 0)
	{
		ft_printfd(2, RED"minishell: ");
		perror(token->value);
		ft_printfd(2, ""NO_ALL);
		return (0);
	}
	close(fd);
	return (1);
}

static bool	check_token_value(t_token *token, t_cmds *new_node)
{
	if (token->type == TOKEN_INFILE)
	{
		if (!check_fd(token))
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
	
	// Controlla se abbiamo ricevuto SIGINT durante readline
	if (g_signal_mode == SIG_INT_RECEIVED)
		return (NULL);
		
	if (!readline_result)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}
	return (ft_strjoin2(readline_result, "\n"));
}

static int	generate_heredoc(t_msh *msh, t_token **tokens, int *j,
	t_cmds *new_node)
{
	int		heredoc_fd;
	char	*str;

	new_node->heredoc_flag = true;
	new_node->limiter = ft_strjoin(tokens[*j]->value, "\n");
	new_node->infile = ft_strjoin2(ft_itoa(*j), "heredoc.txt");
	heredoc_fd = open(new_node->infile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	setup_signals(SIG_HEREDOC);
	while (1)
	{
		if (g_signal_mode == SIG_INT_RECEIVED)
		{
			close(heredoc_fd);
			unlink(new_node->infile);
			new_node->abort_flag = 1;
			msh->exit_status = 130;
			setup_signals(SIG_BACKTOBACK);
			return (0);
		}
		str = get_readline_result("> ");
		if (!str)
		{
			if (g_signal_mode == SIG_INT_RECEIVED)
			{
				close(heredoc_fd);
				unlink(new_node->infile);
				new_node->abort_flag = 1;
				msh->exit_status = 130;
				setup_signals(SIG_BACKTOBACK);
				return (0);
			}
			close(heredoc_fd);
			unlink(new_node->infile);
			new_node->abort_flag = 1;
			msh->exit_status = 130;
			setup_signals(SIG_BACKTOBACK);
			return (0);
		}
		str = ft_expanded_heredoc_cpy(msh, str);
		if (!str)
		{
			setup_signals(SIG_BACKTOBACK);
			return (close(heredoc_fd), 0);
		}
		if (ft_strcmp(new_node->limiter, str) == 0)
		{
			free(str);
			break ;
		}
		ft_printfd(heredoc_fd, "%s", str);
		free(str);
	}
	setup_signals(SIG_BACKTOBACK);
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
