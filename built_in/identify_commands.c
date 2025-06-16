#include "../minishell.h"

int	identify_builtin_commands(t_msh *msh, char **cmd, char *input)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(msh->envp2);
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		ft_export(msh, cmd);
		if (!msh->envp2)
			return (-1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_unset(msh, cmd);
		if (!msh->envp2)
			return (-1);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(msh, cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "clear") == 0)
	{
		ft_clear(msh, input);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(msh, input);
	else
		return (0);
	return (1);
}
