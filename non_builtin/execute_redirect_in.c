#include "../minishell.h"

static void	print_err(char *s1, char *err_type)
{
	write(2, RED"", 5);
	write(2, s1, ft_strlen(s1));
	write(2, err_type, ft_strlen(err_type));
	write(2, NO_ALL"", 4);
}

// Looks for the path of the command "cmd" in the Environment (envp)
/* static char	*find_pathname(char *cmd, char **envp)
{
	char	**paths;
	char	*pathname;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		pathname = ft_strjoin(ft_strdup(paths[i]), "/");
		pathname = ft_strjoin(pathname, cmd);
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
static void	*execute_cmd(char **cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (ft_strchr(cmd[0], '/'))
	{
		execute_absrel_path(cmd[0], envp);
		exit (127);
	}
	cmd_path = find_pathname(cmd[0], envp);
	if (!cmd_path)
		exit (127);
	execve(cmd_path, cmd, envp);
	print_err(cmd[0], ": command not executed.\n");
	free(cmd_path);
	exit (1);
} */

static void	child_exec(t_msh *msh, int infile_fd)
{
	ft_printf(BRCYAN"infile: %s\n"NO_ALL, msh->infiles->infile);/////////////
	while (msh->infiles)
	{
		infile_fd = open(msh->infiles->infile, O_RDONLY);
		if (infile_fd < 0)
		{
			print_err(msh->infiles->infile, ": Could not be opened.\n");
			exit(1);
		}
		msh->infiles = msh->infiles->next;
	}
	dup2(infile_fd, 0);
	close(infile_fd);
}

void	non_builtin_redirect_in(t_msh *msh)
{
	pid_t	id;
	int 	status;
	int		infile_fd;

	status = 0;
	infile_fd = 0;
	// if (msh->pipe_count > 0) || pipe_check(msh)
	id = fork();
	if (id < 0)
	{
		ft_putstr_fd("Fork failed.\n", 2);
		msh->exit_status = 1;
		return ;
	}
	else if (0 == id)
	{
		child_exec(msh, infile_fd);
		execute_cmd(msh->cmds->cmd, msh->envp2);
	}
	while (waitpid(id, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
	}
}
