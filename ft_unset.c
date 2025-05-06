#include "minishell.h"

char	**delete_var(char **envp, int i/* , char *target */)
{
	char	**nenv;
	int		j;

	j = 0;
	nenv = ft_calloc(ft_mtrxlen(envp), sizeof(char *));
	while (j < i)
	{
		nenv[j] = ft_strdup(envp[j]);
		free(envp[j]);
		j++;
	}
	if (j == i)
	{
		free(envp[j]);
		i++;
	}
	while (envp[i])
	{
		nenv[j] = ft_strdup(envp[i]);
		free(envp[i]);
		j++;
		i++;
	}
	return (free(envp), nenv);
}

// Looks for the target Variable in the Environment.
void	take_aim(char **envp, char *target)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = NULL;
	while (envp[i])
	{
		var_name = ft_strchr3(envp[i], '=');
		if (!var_name)
			return (ft_putstr_fd(RED"Malloc failure"NO_ALL, 2));
		if (ft_strncmp(var_name, target, ft_strlen(target)) == 0)
		{
			envp = delete_var(envp, i/* , target */);
			free(var_name);
			break ;
		}
		i++;
		free(var_name);
	}
}

void	ft_unset(t_msh *msh)
{
	int		i;
	char	*target;

	i = 1;
	msh->exit_status = 0;
	target = NULL;
	while (msh->tokens[i])
	{
		target = ft_strdup(msh->tokens[i]->value);
		if (!target)
			return (ft_putstr_fd(RED"Malloc failure"NO_ALL, 2));
		if (ft_strcmp(target, "PATH") == 0)
		{
			msh->env_existence = false;
			break ;
		}
		take_aim(msh->envp2, target);
		i++;
	}
	
	return (free(target));
}
