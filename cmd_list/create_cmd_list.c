#include "../minishell.h"

// Returns the number of TOKEN_WORDs before the next pipe or the end of input.
static size_t	count_w_tokens(t_token **tokens, int *i)
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

void	assign_values(t_token **tokens, int *i, t_cmds *new_node)
{
	int	j;

	j = *i;
	new_node->abort_flag = false;
	new_node->cmd = assign_cmd_value(tokens, i);
	assign_outfile_value(tokens, &j, new_node);
	j = *i;
	assign_infile_value(tokens, &j, new_node);
}

// Returns a list of commands and relative arguments given from input.
t_cmds	*ft_create_cmd_list(t_token **tokens)
{
	t_cmds	*new_node;
	t_cmds	*root;
	t_cmds	*prev;
	int		i;
	int		j;

	new_node = NULL;
	root = NULL;
	prev = NULL;
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_WORD)
		{
			prev = new_node;
			new_node = ft_calloc(count_w_tokens(tokens, &i) + 1, sizeof(t_cmds));
			if (!new_node)
				return (root);
			if (j == 0)
				root = new_node;
			else
				prev->next = new_node;
			assign_values(tokens, &i, new_node);
			if (!new_node->cmd)
			{
				free(new_node);
				return (NULL);
			}
			j++;
		}
		else
			i++;
	}
	printList(root);/////////////////////////////////////
	return (root);
}
