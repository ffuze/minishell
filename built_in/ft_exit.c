/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:40:57 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/08 17:05:21 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_number(char *str)
{
	int	j;

	j = 0;
	if (str[0] == '-' || str[0] == '+')
		j = 1;
	if (!str[j])
		return (0);
	while (str[j])
	{
		if (str[j] < '0' || str[j] > '9')
			return (0);
		j++;
	}
	return (1);
}

int	all_args_int(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!is_valid_number(args[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_msh *msh, char **args)
{
	ft_printfd(2, BRCYAN"exit\n"NO_ALL);
	if (args[1])
	{
		if (!is_valid_number(args[1]))
		{
			ft_printfd(2, \
				RED"pokeshell: exit: %s: numeric argument required\n"NO_ALL, \
																	args[1]);
			free_cmd_list(msh->cmds);
			free_stuff(*msh);
			exit(2);
		}
		if (ft_mtrxlen(args) > 2)
		{
			ft_printfd(2, RED"pokeshell: exit: too many arguments\n"NO_ALL);
			msh->exit_status = 1;
			return ;
		}
		msh->exit_status = ft_atoi(args[1]);
		free_cmd_list(msh->cmds);
		free_stuff(*msh);
		return (exit(msh->exit_status));
	}
	return (free_cmd_list(msh->cmds), free_stuff(*msh), exit(msh->exit_status));
}
