/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:49:03 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/08 16:52:30 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	through_doublequotes(t_msh *msh, char *input, size_t *i)
{
	size_t	j;

	j = ft_strlen(msh->exp_input);
	msh->exp_input[j++] = input[(*i)++];
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			if (!expand_dollar(msh, input, i, &j))
				return (0);
		}
		if (input[*i])
			msh->exp_input[j++] = input[(*i)++];
	}
	if (input[*i] == '"')
		msh->exp_input[j++] = input[(*i)++];
	return (j);
}

static void	through_singlequotes(t_msh *msh, char *input, size_t *i, size_t *j)
{
	msh->exp_input[(*j)++] = input[(*i)++];
	while (input[*i] && input[*i] != '\'')
		msh->exp_input[(*j)++] = input [(*i)++];
	if (input[*i] == '\'')
		msh->exp_input[(*j)++] = input[(*i)++];
}

// Returns the string "input" without outer quotes.
char	*ft_expandedcpy(t_msh *msh, char *input)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] && input[i] != '"' && input[i] != '\'' && input[i] != '$')
			msh->exp_input[j++] = input [i++];
		if (input[i] == '\'')
			through_singlequotes(msh, input, &i, &j);
		if (input[i] == '"')
		{
			j = through_doublequotes(msh, input, &i);
			if (j == 0)
				return (NULL);
		}
		if (input[i] == '$')
		{
			if (!expand_dollar(msh, input, &i, &j))
				return (NULL);
		}
	}
	return (msh->exp_input);
}

// Expands the Environment variables from the input string.
// An error message is diplayed if outer quotes are unclosed.
char	*ft_parse_and_expand(t_msh *msh, char *input)
{
	if (!input[0])
		return (NULL);
	if (ft_parse_input(input) < 0)
		return (NULL);
	msh->exp_input = ft_calloc(ft_strlen(input) + 1, sizeof(char *));
	if (!msh->exp_input)
		return (NULL);
	msh->exp_input = ft_expandedcpy(msh, input);
	if (!msh->exp_input)
		return (NULL);
	return (msh->exp_input);
}
