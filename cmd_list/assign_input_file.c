/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_input_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:54:02 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/03 20:31:07 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks the file descriptor's permissions.
static int	check_fd(t_token *tokens)
{
	int	fd;

	if (ft_strcmp(tokens->value, "") == 0)
	{
		ft_printfd(2, \
			RED"minishell: syntax error found in input redirection\n" \
			NO_ALL);
		return (0);
	}
	fd = open(tokens->value, O_RDONLY);
	if (fd < 0)
	{
		ft_printfd(2, RED"minishell: %s: Permission denied\n"NO_ALL, \
														tokens->value);
		return (0);
	}
	close(fd);
	return (1);
}

static char	*get_readline_result(const char *prompt)
{
	char	*readline_result;

	readline_result = readline(prompt);
	if (!readline_result)
		return (NULL);
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
	while (1)
	{
		str = get_readline_result("> ");
		if (!str)
			return (close(heredoc_fd), 0);
		str = ft_expanded_heredoc_cpy(msh, str);
		if (!str)
			return (close(heredoc_fd), 0);
		if (ft_strcmp(new_node->limiter, str) == 0)
		{
			free(str);
			break ;
		}
		ft_printfd(heredoc_fd, "%s", str);
		free(str);
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
			if (!check_fd(tokens[*j]))
			{
				new_node->abort_flag = true;
				return ;
			}
			free_input_redirection(new_node);
			new_node->infile = ft_strdup(tokens[*j]->value);
		}
		else if (tokens[*j]->type == TOKEN_LIMITER)
		{
			free_input_redirection(new_node);
			generate_heredoc(msh, tokens, j, new_node);
		}
		(*j)++;
	}
}
