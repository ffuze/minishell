/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:05:03 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/17 18:08:44 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_token	*make_token(t_token_enum token_type, char *input, size_t len)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = token_type;
	token->value = ft_strdup(input);
	return (token);
}

t_token	**tokenize(char *input, int token_count)
{
	t_token	**tokens;
	int	i;
	int	count;
	int	start;

	tokens = malloc(sizeof(t_token *));
	i = 0;
	count = 0;
	start = 0;
	while (input[i] != '\0')
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '\'')
		{
			start = ++i;
			while (input[i] != '\'')
				i++;
			tokens[count] = make_token(TOKEN_STRING_SINGLE, ft_strlen(input) + start, );
		}
	}
}