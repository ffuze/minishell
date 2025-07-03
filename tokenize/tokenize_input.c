/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:12:52 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/03 11:35:51 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Tokenizes the single redirection in output (<).
static void	single_redirect(t_token **tokens, char *input, size_t *i, \
																int *count)
{
	size_t	start;

	tokens[(*count)++] = make_token(TOKEN_RE_INPUT, input, *i, 1);
	(*i)++;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '|')
		return ;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|')
		(*i)++;
	tokens[(*count)++] = make_token(TOKEN_INFILE, input, start, *i - start);
}

// Tokenizes the double redirection in output (<<).
static void	double_redirect(t_token **tokens, char *input, size_t *i, \
																int *count)
{
	size_t	start;

	tokens[(*count)++] = make_token(TOKEN_RE_INPUT, input, *i, 2);
	(*i) += 2;
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	start = *i;
	if (input[*i] == '|')
		return ;
	while (input[*i] && input[*i] != ' ' && input[*i] != '|')
		(*i)++;
	tokens[(*count)++] = make_token(TOKEN_LIMITER, input, start, *i - start);
}

// Check for every command block divided by a pipe that has an
//  input redirection wether the input file exists or not; if it does not,
//  print an error message and skip the wholeblock until a next pipe is found.
int	tokenize_input(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count;
	int		starting_count;

	starting_count = count_tokens(tokens);
	count = starting_count;
	if (!tokens || !input || !msh)
		return (0);
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	if (input[*i] == '<' && input[*i + 1] != '<')
		single_redirect(tokens, input, i, &count);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		double_redirect(tokens, input, i, &count);
	return (count - starting_count);
}
