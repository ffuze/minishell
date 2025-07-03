/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:44:11 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/03 11:36:20 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_sintax_err(char *tokenvalue)
{
	ft_printfd(2, \
		RED"minishell: syntax error near token `%s'\n" \
		NO_ALL, tokenvalue);
}

static bool	check_pipe_tokens(t_token **tokens, int *i)
{
	if (!tokens[(*i) + 1] || *i == 0)
		return (print_sintax_err(tokens[*i]->value), false);
	else if (tokens[(*i) + 1]->type == TOKEN_PIPE)
		return (print_sintax_err(tokens[*i]->value), false);
	else if (tokens[(*i) + 1]->type == TOKEN_RE_INPUT && \
		(!tokens[(*i) + 2] || !tokens[(*i) + 2]->value[0]))
		return (print_sintax_err(tokens[*i]->value), false);
	else if (tokens[(*i) + 1]->type == TOKEN_RE_OUTPUT && \
		(!tokens[(*i) + 2] || !tokens[(*i) + 2]->value[0]))
		return (print_sintax_err(tokens[*i]->value), false);
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
		return (false);
	return (true);
}
