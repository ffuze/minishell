/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:54:20 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:32 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
char	*ft_expanded_heredoc_cpy(t_msh *msh, char *str)
{
	size_t	i;
	size_t	j;
	char	*expanded_s;

	i = 0;
	j = 0;
	expanded_s = NULL;
	if (!str)
		return (NULL);
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
