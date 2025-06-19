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
		pathname = ft_strjoin2(ft_strdup(paths[i]), "/");
		pathname = ft_strjoin2(pathname, cmd);
		if (!pathname)
			return (free_dpc(paths), NULL);
		if (0 == access(pathname, F_OK | X_OK))
			return (free_dpc(paths), pathname);
		free(pathname);
		i++;
	}
	free_dpc(paths);
	return (print_err(cmd, ": command not found.\n"), NULL);
}

// Executes a command with the given absolute or relative path
static void	*execute_absrel_path(char *cmd, char **envp)
{
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return (NULL);
	if (access(split_cmd[0], F_OK | X_OK | R_OK) != 0)
	{
		print_err(cmd, ": permission denied.\n");
		free_dpc(split_cmd);
		return (NULL);
	}
	execve(split_cmd[0], split_cmd, envp);
	print_err(cmd, ": No such file or directory.\n");
	return (free_dpc(split_cmd), NULL);
}

// If a '/' is present in the cmd string, an absolute/relative path was given
//  to the command from input and it won't be searched in the Environment
void	execute_cmd(t_msh *msh, char **cmd, char **envp, char *input)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (execute_builtin_commands(msh, cmd, input) != 0)///////////////////
	{
		liberate_fdmatrix(msh->fd_mrx, msh->pipe_count);
		free_everything(*msh, input);
		free_cmd_list(msh->cmds);
		exit(EXIT_SUCCESS);
	}
	if (ft_strchr(cmd[0], '/'))
	{
		execute_absrel_path(cmd[0], envp);
		exit (127);
	}
	cmd_path = find_pathname(cmd[0], envp);
	if (!cmd_path)
	{
		liberate_fdmatrix(msh->fd_mrx, msh->pipe_count);
		free_everything(*msh, input);
		free_cmd_list(msh->cmds);
		exit (127);
	}
	execve(cmd_path, cmd, envp);
	// print_err(cmd[0], ": command not executed.\n");
	// free(cmd_path);
	// exit (1);
}
