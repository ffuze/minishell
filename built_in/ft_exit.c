#include "../minishell.h"

int	all_args_int(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		int j = 0;
		if (args[i][0] == '-' || args[i][0] == '+')
			j = 1;
		if (!args[i][j])
			return (0);
		while (args[i][j])
		{
			if (args[i][j] < '0' || args[i][j] > '9')
				return (0);
			j++;
		}
		if (typeof(args[i] != int))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_msh *msh, char **args)
{
	int	exit_status;
	
	exit_status = 0;
	if (args[2])
	{
		ft_printf("pokeshell: exit: too many arguments\n");
		return;
	}
	else if (args[1] && !all_args_int(args))
	{
		ft_printf("pokeshell: exit: %s: numeric argument required\n", args[1]);
		return;
	}
	if (args && args[1])
	{
		exit_status = ft_atoi(args[1]);
		exit_status = exit_status % 256;
		if (exit_status < 0)
			exit_status = 256 + exit_status;
	}
	free_cmd_list(msh->cmds);
	free_everything(*msh);
	exit(exit_status);
}
// limite exit status: 255`