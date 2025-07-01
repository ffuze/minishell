#include "../minishell.h"

int	identify_builtin_commands(char **cmd)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin_commands(t_msh *msh, char **cmd)
{
	if (ft_strcmp(cmd[0], "pwd") == 0)
		msh->exit_status = ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		msh->exit_status = ft_cd(msh, cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		msh->exit_status = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		msh->exit_status = ft_env(msh->envp2);
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		msh->exit_status = ft_export(msh, cmd);
		if (!msh->envp2)
			return (-1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		msh->exit_status = ft_unset(msh, cmd);
		if (!msh->envp2)
			return (-1);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(msh, cmd), 1);
	else
		return (1);
	return (0);
}
