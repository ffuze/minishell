/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_output_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:50:44 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/07 16:52:35 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Checks the file descriptor's permissions.
static int	check_fd_out(t_token *token)
{
	int	fd;

	if (ft_strcmp(token->value, "") == 0)
	{
		ft_printfd(2, \
			RED"minishell: syntax error found in output redirection\n" \
			NO_ALL);
		return (0);
	}
	fd = access(token->value, W_OK);
	if (fd < 0)
	{
		ft_printfd(2, RED"minishell: ");
		perror(token->value);
		ft_printfd(2, ""NO_ALL);
	}
	fd = open(token->value, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

// Assigns to the relative command list node the name of the 
//  output redirection file. Sets it to NULL if there is none.
void	assign_outfile_value(t_token **tokens, int *j, t_cmds *new_node)
{
	new_node->outfile = NULL;
	new_node->append_flag = false;
	while (*j > 0 && tokens[*j - 1]->type != TOKEN_PIPE)
		(*j)--;
	while (tokens[*j] && tokens[*j]->type != TOKEN_PIPE)
	{
		if (tokens[*j]->type == TOKEN_OUTFILE)
		{
			if (!check_fd_out(tokens[*j]))
			{
				new_node->abort_flag = true;
				return ;
			}
			if (new_node->outfile)
				free(new_node->outfile);
			new_node->outfile = ft_strdup(tokens[*j]->value);
			if (tokens[*j - 1]->value[1] == '>')
				new_node->append_flag = true;
		}
		(*j)++;
	}
}
