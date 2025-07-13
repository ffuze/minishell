/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 21:08:55 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/13 17:43:36 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*make_token(t_token_enum token_type, char *input, size_t start, \
																size_t end)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->value = ft_substr(input, start, end);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

int	count_tokens(t_token **tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens[count])
		count++;
	return (count);
}

// Checks the file descriptor's permissions.
bool	check_fd_in(t_token *token)
{
	int	fd;

	if (!token->value || !token->value[0])
	{
		ft_printfd(2, \
			RED"minishell: syntax error found in input redirection\n" \
			NO_ALL);
		return (0);
	}
	fd = access(token->value, F_OK | R_OK);
	if (fd < 0)
	{
		ft_printfd(2, RED"minishell: ");
		perror(token->value);
		ft_printfd(2, ""NO_ALL);
		return (0);
	}
	return (1);
}
