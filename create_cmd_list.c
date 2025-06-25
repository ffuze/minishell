#include "minishell.h"

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

// Concatenates TOKEN_WORDs not separated by a pipe in a single command array.
static char	**assign_cmd_value(t_token **tokens, int *i)
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
//-----------------------------------------------------------------------------
// Check if the fd has got permissions or not
static int	check_fd(t_token *tokens)
{
	int	fd;
	if (ft_strcmp(tokens->value, "") == 0)
	{
		ft_printfd(2, \
			RED"minishell: syntax error near unexpected token `newline'\n" \
			NO_ALL);
		return (0);
	}
	fd = open(tokens->value, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_printfd(2, RED"minishell: %s: Permission denied\n"NO_ALL, \
														tokens->value);
		return (0);
	}
	close(fd);
	return (1);
}

// Assigns to the relative command list node the name of the 
//  output redirection file. Sets it to NULL if there is none.
static void	assign_outfile_value(t_token **tokens, int *i, t_cmds *new_node)
{
	int	j;

	j = *i;
	new_node->append_flag = false;
	new_node->outfile = NULL;
	while (j > 0 && tokens[j] && tokens[j - 1] && tokens[j - 1]->type != TOKEN_PIPE)
		j--;
	while (tokens[j] && tokens[j]->type != TOKEN_PIPE)
	{
		if (tokens[j]->type == TOKEN_OUTFILE)
		{
			if (!check_fd(tokens[j]))
			{
				new_node->abort_flag = true;
				return ;
			}
			if (new_node->outfile)
				free(new_node->outfile);
			new_node->outfile = ft_strdup(tokens[j]->value);
			if (tokens[j - 1]->value[1] == '>')
				new_node->append_flag = true;
		}
		j++;
	}
}
//-----------------------------------------------------------------------------

void	assign_values(t_token **tokens, int *i, t_cmds *new_node)
{
	int	j;

	j = *i;
	new_node->abort_flag = false;
	new_node->cmd = assign_cmd_value(tokens, i);
	assign_outfile_value(tokens, &j, new_node);
	// new_node->infile = assign_infi_value(tokens, &i);
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
