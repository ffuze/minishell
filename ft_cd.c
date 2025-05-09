#include "minishell.h"

// Sets the Exit Status and prints what kind of error was met.
void	cd_err(t_msh *msh)
{
	msh->exit_status = 1;
	write(2, "\e[31;1m", 7);
	ft_putstr_fd(msh->tokens[1]->value, 2);
	write(2, NO_ALL, 4);
	write(2, RED": ", 7);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n"NO_ALL, 5);
}

// Moves to the previous directory.
void	to_prev_dir(t_msh *msh, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		i++;
	if (chdir(ft_strchr2(envp[i], '=')) < 0)
		cd_err(msh);
	ft_printf("%s\n", ft_strchr2(envp[i], '='));
}

void	ft_cd(t_msh *msh)
{
	if (!msh->tokens[1] || ft_strcmp(msh->tokens[1]->value, "~") == 0)
	{
		if (chdir("/nfs/homes/lemarino") < 0)
			cd_err(msh);
	}
	else if (msh->tokens[2])
	{
		msh->exit_status = 1;
		ft_putstr_fd(RED"cd: too many arguments\n"NO_ALL, 2);
	}
	else if (ft_strcmp(msh->tokens[1]->value, "-") == 0)
		to_prev_dir(msh, msh->envp2);
	else
		if (chdir(msh->tokens[1]->value) < 0)
			cd_err(msh);
}
