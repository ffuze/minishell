#include "../minishell.h"

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

// Allocates memory for every node of the commands list.
static t_cmds	*ft_create_cmd_nodes(t_msh *msh, t_token **tokens, int *i, \
																		int *j)
{
	t_cmds	*new_node;
	t_cmds	*prev;

	while (tokens[*i])
	{
		if (tokens[*i]->type == TOKEN_WORD || \
						(tokens[*i + 1] && tokens[*i + 1]->type == TOKEN_PIPE))
		{
			prev = new_node;
			new_node = ft_calloc(count_w_token(tokens, i) + 1, sizeof(t_cmds));
			if (!new_node)
				return (msh->cmds);
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
	t_cmds	*new_node;
	t_cmds	*prev;
	int		i;
	int		j;

	new_node = NULL;
	msh->cmds = NULL;
	prev = NULL;
	i = 0;
	j = 0;
	msh->cmds = ft_create_cmd_nodes(msh, tokens, &i, &j);
	printList(msh->cmds);/////////////////////////////////////
	return (msh->cmds);
}
