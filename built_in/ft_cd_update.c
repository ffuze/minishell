/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:39:59 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/01 20:44:20 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(char **envp)
{
	int		i;
	char	*current_dir;

	i = 0;
	current_dir = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PWD", 3) != 0)
		i++;
	if (!envp[i])
		return ;
	if (ft_strncmp(envp[i], "PWD=", 4) != 0)
	{
		envp[i] = ft_strjoin2(envp[i], "=");
		envp[i] = ft_strjoin3(envp[i], getcwd(current_dir, PATH_MAX));
	}
	else
	{
		free(envp[i]);
		current_dir = getcwd(current_dir, PATH_MAX);
		envp[i] = ft_strjoin("PWD=", current_dir);
		free(current_dir);
	}
}

void	update_oldpwd(char **envp)
{
	int		i;
	char	*current_dir;

	i = 0;
	current_dir = NULL;
	while (envp[i] && ft_strncmp(envp[i], "OLDPWD", 6) != 0)
		i++;
	if (!envp[i])
		return ;
	if (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
	{
		envp[i] = ft_strjoin2(envp[i], "=");
		envp[i] = ft_strjoin3(envp[i], getcwd(current_dir, PATH_MAX));
	}
	else
	{
		free(envp[i]);
		current_dir = getcwd(current_dir, PATH_MAX);
		envp[i] = ft_strjoin("OLDPWD=", current_dir);
		free(current_dir);
	}
}
