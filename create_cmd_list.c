#include "minishell.h"

// Returns the number of consecutive TOKEN_WORD
static size_t	count_w_tokens(t_token **tokens, int *i)
{
	int		j;
	size_t	count;

	j = *i;
	count = 0;
	while (tokens[j] && tokens[j]->type == TOKEN_WORD)
	{
		j++;
		count++;
	}
	return (count);
}

// Al momento alloca solo la matrice e non le singole stringhe
static char	**assign_value(t_token **tokens, int *i)
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
		cmd[j++] = tokens[(*i)++]->value;
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

	i = 0;
	j = 0;
	new_node = NULL;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_WORD)
		{

			prev = new_node;
			new_node = ft_calloc(count_w_tokens(tokens, &i) + 1, sizeof(t_cmds));
			if (!new_node)
				return (NULL);
			if (j == 0)
				root = new_node;
			else
				prev->next = new_node;
			new_node->cmd = assign_value(tokens, &i);
			if (!new_node->cmd)
				return (NULL);
			j++;
		}
		if (tokens[i])
			i++;
	}
	// printList(root);
	return (root);
}
