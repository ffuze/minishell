/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:24:32 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:32 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Swaps the ~ symbol with HOME path and moves to the indicated directory.
static void	get_dir(t_msh *msh, char *home_path, char *input)
{
	char	*path;

	path = NULL;
	update_oldpwd(msh->envp2);
	if (strncmp(input, "~/", 2) == 0)
		path = ft_strjoin(home_path, ft_strchr(input, '/'));
	else
		path = ft_strdup(input);
	if (chdir(path) < 0)
	{
		ft_printfd(2, RED"%s: %s\n"NO_ALL, path, strerror(errno));
		msh->exit_status = 1;
	}
	free(path);
}

// Moves to the previous directory.
static void	to_prev_dir(t_msh *msh, char **envp)
{
	int	i;

	i = 0;
	update_oldpwd(msh->envp2);
	while (envp[i] && ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		i++;
	if (!envp[i])
	{
		ft_printfd(2, RED"OLDPWD not set\n"NO_ALL);
		msh->exit_status = 1;
		return ;
	}
	if (chdir(ft_strchr2(envp[i], '=')) < 0)
	{
		ft_printfd(2, RED"%s: %s\n"NO_ALL, \
							ft_strchr2(envp[i], '='), strerror(errno));
		msh->exit_status = 1;
		return ;
	}
	ft_printf("%s\n", ft_strchr2(envp[i], '='));
}

static char	*find_home(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "HOME=", 5) != 0)
		i++;
	if (!envp[i])
	{
		ft_printfd(2, RED"HOME not found\n"NO_ALL);
		return (NULL);
	}
	return (ft_strchr2(envp[i], '='));
}

int	ft_cd(t_msh *msh, char **cmd)
{
	char	*home_path;

	home_path = find_home(msh->envp2);
	if (!home_path)
		return (1);
	if (cmd[1] && cmd[2])
		return (ft_putstr_fd(RED"cd: too many arguments\n"NO_ALL, 2), 1);
	else if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
	{
		update_oldpwd(msh->envp2);
		if (chdir(home_path) < 0)
		{
			ft_printfd(2, RED"%s: %s\n"NO_ALL, home_path, strerror(errno));
			return (1);
		}
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
		to_prev_dir(msh, msh->envp2);
	else if (ft_strcmp(cmd[1], ".") == 0)
		update_oldpwd(msh->envp2);
	else
		get_dir(msh, home_path, cmd[1]);
	update_pwd(msh->envp2);
	return (0);
}
