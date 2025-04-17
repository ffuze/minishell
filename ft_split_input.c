/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:18:23 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/17 12:05:03 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	handle_squotes(char *input_i)
{}

int	check_quotes(char *input_i)
{
	int	j;

	j = 0;
	while (input_i[j] != 34 && input_i[j] != 39)
		j++;
	if (input_i[j] == 34)
	{
		handle_squotes(input_i + j);
	}
	else if (input_i[j] == 39)
	{}
	return (1);
} */

// Returns the input as an array of strings after handling quotes
char	**ft_split_input(char *input)
{
	char	**split_input;
	int		i;

	i = 0;
	split_input = ft_split(input, ' ');
	if (!split_input)
		return (NULL);
	while (split_input)
	{
		if (!check_quotes(&split_input[i]))
			return (free_dpc(split_input));
		i++;
	}
}
