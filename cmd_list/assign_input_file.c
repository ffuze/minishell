#include "../minishell.h"

// Checks the file descriptor's permissions.
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

// Expands environment variables and/or the exit status.
// Returns NULL on failure.
static char	*expand_heredoc_dollar(t_msh *msh, char *input, size_t *i, \
																size_t *j)
{
	char	*expanded_s;

	expanded_s = ft_calloc(1, 1);
	if (input[(*i) + 1] == '?')
	{
		expanded_s = ft_strjoin3(expanded_s, ft_itoa(msh->exit_status));
		(*i) += 2;
	}
	else
	{
		expanded_s = ft_strjoin2(expanded_s, \
						find_value(msh->envp2, input, i));
	}
	if (!expanded_s)
		return (NULL);
	*j = ft_strlen(expanded_s);
	expanded_s = ft_realloc(expanded_s, *j, \
										*j + ft_strlen(input) - *i);
	if (!expanded_s)
		return (NULL);
	expanded_s = ft_strjoin2(expanded_s, "\n");
	return (expanded_s);
}

// Returns the string "str" with expanded variables.
// Returns NULL on failure.
static char	*ft_expanded_heredoc_cpy(t_msh *msh, char *str)
{
	size_t	i;
	size_t	j;
	char	*expanded_s;

	i = 0;
	j = 0;
	expanded_s = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			expanded_s = expand_heredoc_dollar(msh, str, &i, &j);
			if (!expanded_s)
				return (NULL);
		}
		if (str[i])
			i++;
	}
	if (!expanded_s)
		return (str);
	free(str);
	return (expanded_s);
}

static char *get_readline_result(const char *prompt)
{
    char	*readline_result;
	
	readline_result = readline(prompt);
    if (!readline_result)
        return (NULL);
    return (ft_strjoin2(readline_result, "\n"));
}

static void generate_heredoc(t_msh *msh, t_token **tokens, int *j,
	t_cmds *new_node)
{
    int     heredoc_fd;
    char    *str;
    
    new_node->heredoc_flag = true;
    new_node->limiter = ft_strjoin(tokens[*j]->value, "\n");
    new_node->infile = ft_strjoin2(ft_itoa(*j), "heredoc.txt");
    heredoc_fd = open(new_node->infile, O_WRONLY | O_APPEND | O_CREAT, 0644);
    while (1)
    {
        str = get_readline_result("> ");
        if (!str)
        {
            close(heredoc_fd);
            return ;
        }
        str = ft_expanded_heredoc_cpy(msh, str);
        if (!str)
        {
            close(heredoc_fd);
            return ;
        }
        if (ft_strcmp(new_node->limiter, str) == 0)
        {
            free(str);
            break ;
        }
        ft_printfd(heredoc_fd, "%s", str);
        free(str);
    }
    close(heredoc_fd);
}

// static void	generate_heredoc(t_msh *msh, t_token **tokens, int *j,
// 															t_cmds *new_node)
// {
// 	int		heredoc_fd;
// 	char	*str;

// 	new_node->heredoc_flag = true;
// 	new_node->limiter = ft_strjoin(tokens[*j]->value, "\n");
// 	new_node->infile = ft_strjoin2(ft_itoa(*j), "heredoc.txt");
// 	heredoc_fd = open(new_node->infile, O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	str = ft_strjoin2(readline("> "), "\n");
// 	str = ft_expanded_heredoc_cpy(msh, str);
// 	while (ft_strcmp(new_node->limiter, str) != 0)
// 	{
// 		ft_printfd(heredoc_fd, "%s", str);
// 		free(str);
// 		str = ft_strjoin2(readline("> "), "\n");
// 		str = ft_expanded_heredoc_cpy(msh, str);
// 	}
// 	free(str);
// 	close(heredoc_fd);
// }

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
