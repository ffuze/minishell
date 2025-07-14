/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 21:08:55 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:32 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	through_doublequotes(char *input, int *i, int *l)
{
	(*i)++;
	(*l)++;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (!input[*i])
	{
		ft_printfd(2, RED"Double quotes unclosed.\n"NO_ALL);
		*l = -1;
		return ;
	}
	(*i)++;
	return ;
}

static void	through_singlequotes(char *input, int *i, int *l)
{
	(*i)++;
	(*l)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
	{
		ft_printfd(2, RED"Single quotes unclosed.\n"NO_ALL);
		*l = -1;
		return ;
	}
	(*i)++;
	return ;
}

// Checks whether there are unclosed quotes.
int	ft_parse_input(char *input)
{
	int		i;
	int		l;

	i = 0;
	l = 0;
	while (l >= 0 && input[i])
	{
		if (l >= 0 && input[i] == '"')
			through_doublequotes(input, &i, &l);
		if (l >= 0 && input[i] == '\'')
			through_singlequotes(input, &i, &l);
		if (l >= 0 && input[i] && input[i] != '"' && input[i] != '\'')
		{
			i++;
			l++;
		}
	}
	return (l);
}
