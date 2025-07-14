/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:15:59 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:32 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Prints all the environment variables
int	ft_env(char **envp2)
{
	int	i;

	i = 0;
	while (envp2[i])
	{
		if (ft_strchr(envp2[i], '='))
			ft_printfd(1, "%s\n", envp2[i++]);
		else
			i++;
	}
	return (0);
}
