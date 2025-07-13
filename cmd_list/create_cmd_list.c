/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:49:46 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/08 17:21:35 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

///////////////////////////////////////////////////////////////////////////////
void	printList(t_cmds *head)
{
	t_cmds	*current;
	int		i;

	current = head;
	i = 0;
	int j = 0;
	while (current && current->cmd)
	{
		i = 0;
		ft_printf(RED"##"NO_ALL);
		if (current->cmd)
		{
			while (current && current->cmd && current->cmd[i])
			{
				ft_printf(YELLOW" %s "NO_ALL, current->cmd[i]);
				i++;
				j++;
			}
			ft_printf(MAGENTA"abrt_flag: %d, "NO_ALL, current->abort_flag);
			ft_printf(BLUE"from: %s, "NO_ALL, current->infile);
			ft_printf(BLUE"heredoc: %d, "NO_ALL, current->heredoc_flag);
			ft_printf(BRCYAN"in: %s, "NO_ALL, current->outfile);
			ft_printf(BRCYAN"append: %d, "NO_ALL, current->append_flag);
		}
		else
			ft_printf(YELLOW" (cmd array is NULL) "NO_ALL);
		ft_printf(GREEN"##\n"NO_ALL);
		current = current->next;
	}
}
/////////////////////////////////////////////////////////////////////////////

// Returns the number of TOKEN_WORDs before the next pipe or the end of input.
static size_t	count_w_token(t_token **tokens, int *i)
{
	int		j;
	size_t	count;

	j = *i;
	count = 0;
	while (tokens[j] && tokens[j]->type != TOKEN_PIPE)
	{
		if (tokens[j]->type == TOKEN_WORD)
			count++;
		j++;
	}
	return (count);
}

// Sets the variables for commands and redirections.
void	assign_values(t_msh *msh, t_token **tokens, int *i, t_cmds *new_node)
{
	int	j;

	j = *i;
	new_node->abort_flag = false;
	new_node->cmd = assign_cmd_value(tokens, i);
	if (!new_node->cmd)
		return ;
	assign_outfile_value(tokens, &j, new_node);
	j = *i;
	assign_infile_value(msh, tokens, &j, new_node);
}

// A function to avoid making a new node upon finding a pipe if a command was
//  already found before.
static bool	backtrack_setter(t_msh *msh, t_token **tokens, int *i)
{
	if (tokens[*i]->type == TOKEN_WORD)
	{
		msh->backtrackflag = true;
		return (true);
	}
	else if (tokens[*i + 1]->type == TOKEN_PIPE && msh->backtrackflag == true)
	{
		msh->backtrackflag = false;
		return (false);
	}
	else if (tokens[*i + 1]->type == TOKEN_PIPE && msh->backtrackflag == false)
	{
		return (true);
	}
	return (true);
}

// Allocates memory for every node of the commands list.
static t_cmds	*ft_create_cmd_nodes(t_msh *msh, t_token **tokens, int *i, \
																		int *j)
{
	t_cmds	*new_node;
	t_cmds	*prev;

	while (tokens && tokens[*i])
	{
		if ((tokens[*i]->type == TOKEN_WORD || (tokens[*i + 1] && \
				tokens[*i + 1]->type == TOKEN_PIPE)) \
					&& backtrack_setter(msh, tokens, i))
		{
			prev = new_node;
			new_node = ft_calloc(count_w_token(tokens, i) + 1, sizeof(t_cmds));
			if ((*j)++ == 0)
				msh->cmds = new_node;
			else
				prev->next = new_node;
			assign_values(msh, tokens, i, new_node);
			if (tokens[*i] && tokens[*i + 1] && \
											tokens[*i + 1]->type == TOKEN_PIPE)
				*i += 1;
		}
		else
			*i += 1;
	}
	return (msh->cmds);
}

// Returns a list of commands and relative arguments given from input.
t_cmds	*ft_create_cmd_list(t_msh *msh, t_token **tokens)
{
	int		i;
	int		j;

	msh->cmds = NULL;
	i = 0;
	j = 0;
	msh->cmds = ft_create_cmd_nodes(msh, tokens, &i, &j);
	printList(msh->cmds);
	return (msh->cmds);
}
