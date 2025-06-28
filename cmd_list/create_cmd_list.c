#include "../minishell.h"

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

static void	assign_infile_value(t_token **tokens, int *j, t_cmds *new_node)
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
			new_node->heredoc_flag = true;
			new_node->infile = ft_strjoin2(ft_itoa(*j), "heredoc.txt");
			new_node->limiter = ft_strjoin(tokens[*j]->value, "\n");
			int		heredoc_fd;
			char	*str;
			heredoc_fd = open(new_node->infile, O_WRONLY | O_APPEND | O_CREAT, 0644);
			str = ft_strjoin2(readline("> "), "\n");
			while (ft_strcmp(new_node->limiter, str) != 0)
			{
				ft_printfd(heredoc_fd, "%s", str);
				free(str);
				str = ft_strjoin2(readline("> "), "\n");
			}
			free(str);
			close(heredoc_fd);
		}
		(*j)++;
	}
}
//-----------------------------------------------------------------------------

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
