/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <adegl-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:44:11 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/08 16:22:26 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	open_heredoc(char *limiter, char *infile)
{
	char	*str;
	int		heredocfd;

	heredocfd = open(infile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(limiter, str) == 0)
			return (unlink(infile), free(infile), close(heredocfd), free(str));
		ft_printfd(heredocfd, "%s", str);
		free(str);
	}
}

// Pointlessly executes heredocs in absence of commands. 
static void	hc_heredoc(t_token **tokens)
{
	int		i;
	char	*limiter;
	char	*infile;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_INFILE || \
					tokens[i]->type == TOKEN_OUTFILE)
		{
			if (!tokens[i]->value || !tokens[i]->value[0])
				return (print_syntax_err(tokens[i - 1]->value));
			else if (!check_fd_in(tokens[i]))
				return ;
		}
		else if (tokens[i]->type == TOKEN_LIMITER)
		{
			if (!tokens[i]->value || !tokens[i]->value[0])
				return (print_syntax_err(tokens[i - 1]->value));
			limiter = tokens[i]->value;
			infile = ft_strjoin2(ft_itoa(i + 157), "heredoc.txt");
			open_heredoc(limiter, infile);
		}
		i++;
	}
}

static bool	check_pipe_tokens(t_token **tokens, int *i)
{
	if (!tokens[(*i) + 1] || *i == 0)
		return (print_syntax_err(tokens[*i]->value), false);
	else if (tokens[(*i) + 1]->type == TOKEN_PIPE)
		return (print_syntax_err(tokens[*i]->value), false);
	else if (tokens[(*i) + 1]->type == TOKEN_RE_INPUT && \
		(!tokens[(*i) + 2] || !tokens[(*i) + 2]->value[0]))
		return (print_syntax_err(tokens[*i]->value), false);
	else if (tokens[(*i) + 1]->type == TOKEN_RE_OUTPUT && \
		(!tokens[(*i) + 2] || !tokens[(*i) + 2]->value[0]))
		return (print_syntax_err(tokens[*i]->value), false);
	return (true);
}

static bool	search_word_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] && tokens[i]->type != TOKEN_WORD)
		i++;
	if (tokens[i] && tokens[i]->type == TOKEN_WORD)
		return (true);
	else
		return (false);
}

// Checks whether the tokenized strings are acceptable and/or 
//  are associated to the needed token.
bool	check_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	if (!tokens[0])
		return (false);
	else if (ft_strcmp(tokens[0]->value, ".") == 0)
	{
		ft_printfd(2, \
			RED"minishell: filename argument required `%s'\n" \
			NO_ALL, tokens[i]->value);
		return (false);
	}
	while (tokens[i])
	{
		if (tokens[i]->type == TOKEN_PIPE)
		{
			if (!check_pipe_tokens(tokens, &i))
				return (false);
		}
		i++;
	}
	if (!search_word_tokens(tokens))
		return (hc_heredoc(tokens), false);
	return (true);
}
