/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:48:13 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/05 16:05:13 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Looks for the path of the command "cmd" in the Environment (envp)
static char	*find_pathname(char *cmd, char **envp)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	pathname = "";
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		pathname = ft_strjoin2(ft_strjoin2(ft_strdup(paths[i]), "/"), cmd);
		if (!pathname)
			return (free_dpc(paths), NULL);
		if (0 == access(pathname, F_OK | X_OK))
			return (free_dpc(paths), pathname);
		free(pathname);
		i++;
	}
	return (free_dpc(paths), print_err(cmd, ": command not found.\n"), NULL);
}

// Executes a command with the given absolute or relative path
static void	*execute_absrel_path(char **cmd, char **envp)
{
	if (access(cmd[0], F_OK | X_OK | R_OK) != 0)
	{
		print_err(cmd[0], ": couldn't access.\n");
		free_dpc(cmd);
		return (NULL);
	}
	execve(cmd[0], cmd, envp);
	print_err(cmd[0], ": No such file or directory.\n");
	return (NULL);
}

// If a '/' is present in the cmd string, an absolute/relative path was given
//  to the command from input and it won't be searched in the Environment
void	execute_cmd(t_msh *msh, char **cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (execute_builtin_commands(msh, cmd) != 1)
	{
		free_everything(msh);
		exit(EXIT_SUCCESS);
	}
	if (ft_strchr(cmd[0], '/'))
	{
		execute_absrel_path(cmd, envp);
		free_everything(msh);
		exit (127);
	}
	cmd_path = find_pathname(cmd[0], envp);
	if (!cmd_path)
	{
		free_everything(msh);
		exit (127);
	}
	execve(cmd_path, cmd, envp);
	ft_printfd(2, RED"Command not executed\n"NO_ALL);
	free(cmd_path);
	free_everything(msh);
	exit(127);
}
