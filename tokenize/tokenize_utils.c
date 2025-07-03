/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <adegl-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 21:08:55 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/03 15:54:29 by adegl-in         ###   ########.fr       */
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
