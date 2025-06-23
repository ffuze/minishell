#include "minishell.h"

// Returns the number of TOKEN_WORDs before the next pipe or the end of input.
static size_t	count_w_tokens(t_token **tokens, int *i)
{
	int		j;
	size_t	count;

	j = *i;
	count = 0;
	while (tokens[j] && tokens[j]->type != TOKEN_PIPE)//tokens[j]->type == TOKEN_WORD
	{
		if (tokens[j]->type == TOKEN_WORD)
			count++;
		j++;
	}
	return (count);
}

// Concatenates TOKEN_WORDs not separated by a pipe in a single command array.
static char	**assign__cmd_value(t_token **tokens, int *i)
{
	char	**cmd;
	size_t	n_word_tokens;
	size_t	j;

	j = 0;
	n_word_tokens = count_w_tokens(tokens, i);
	cmd = ft_calloc(n_word_tokens + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (j < n_word_tokens)
	{
		if (tokens[*i]->type == TOKEN_WORD)
			cmd[j++] = tokens[*i]->value;
		(*i)++;
	}
	return (cmd);
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
			new_node->cmd = assign_cmd_value(tokens, &i);
			//new_node->oufile = assign_outfi_value(tokens, &i);
			//new_node->infile = assign_infi_value(tokens, &i);
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
	// printList(root);/////////////////////////////////////
	return (root);
}
