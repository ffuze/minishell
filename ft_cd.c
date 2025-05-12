#include "minishell.h"

// Sets the Exit Status and prints what kind of error was met.
void	cd_err(t_msh *msh, char *path)
{
	msh->exit_status = 1;
	write(2, "\e[31;1m", 7);
	ft_putstr_fd(path, 2);
	write(2, NO_ALL, 4);
	write(2, RED": ", 7);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n"NO_ALL, 5);
}

// Swaps the ~ symbol with HOME path and moves to the indicated directory.
void	get_dir(t_msh *msh, char *home_path, char *input)
{
	char	*path;

	path = NULL;
	if (strncmp(input, "~/", 2) == 0)
		path = ft_strjoin(home_path, ft_strchr(input, '/'));
	else
		path = ft_strdup(input);
	if (chdir(path) < 0)
		cd_err(msh, path);
	free(path);
}

// Moves to the previous directory.
void	to_prev_dir(t_msh *msh, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		i++;
	if (!envp[i])
	{
		ft_printf("OLDPWD not found\n");
		return ;
	}
	if (chdir(ft_strchr2(envp[i], '=')) < 0)
		cd_err(msh, ft_strchr2(envp[i], '='));
	ft_printf("%s\n", ft_strchr2(envp[i], '='));
}

char	*find_home(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "HOME=", 5) != 0)
		i++;
	if (!envp[i])
	{
		ft_printf("HOME not found\n");
		return (NULL);
	}
	return (ft_strchr2(envp[i], '='));
}

void	ft_cd(t_msh *msh)
{
	char	*home_path;

	home_path = find_home(msh->envp2);
	if (!home_path)
		return ;
	if (!msh->tokens[1] || ft_strcmp(msh->tokens[1]->value, "~") == 0)
	{
		if (chdir(home_path) < 0)
			cd_err(msh,home_path);
	}
	else if (msh->tokens[2])
	{
		msh->exit_status = 1;
		ft_putstr_fd(RED"cd: too many arguments\n"NO_ALL, 2);
	}
	else if (ft_strcmp(msh->tokens[1]->value, "-") == 0)
		to_prev_dir(msh, msh->envp2);
	else
		get_dir(msh, home_path, msh->tokens[1]->value);
}
// cd - Desktop | echo ciao
// ciao
// bash: cd: too many arguments