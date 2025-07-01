/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:49:03 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/01 21:24:43 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	skip_spaces(t_token *input, int i)
{
	while (input->value[i] && input->value[i] == ' ')
		i++;
	return (i);
}

// Duplicates the pointer to Environment Variables
char	**ft_envp_dup(char **envp)
{
	char	**envp2;
	int		i;

	i = 0;
	size_t	l;
	l = ft_mtrxlen(envp);
	envp2 = ft_calloc((l + 2), sizeof(char *));
	if (!envp2)
		return (NULL);
	while (envp[i])
	{
		envp2[i] = ft_strdup(envp[i]);
		if (!envp2[i])
			return (free_dpc(envp2), NULL);
		i++;
	}
	return (envp2);
}

int	ft_isbashprint(int c)
{
	if (c > 32 && c < 126 && c != '~' && c != '`' && c != '<' && c != '>'\
						&& c != '(' && c != ')' && c != '^' && c != '|')
		return (1);
	return (0);
}

int	ft_isoperator(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	print_err(char *s1, char *err_type)
{
	write(2, RED"", 5);
	write(2, s1, ft_strlen(s1));
	write(2, err_type, ft_strlen(err_type));
	write(2, NO_ALL"", 4);
}
