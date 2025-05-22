#include "../minishell.h"

// Adds the new variable to the Environment.
static char	**add_var(char **envp, char *new_var)
{
	size_t	new_len;
	size_t	i;
	size_t	j;
	char	**nenvp;

	i = 0;
	j = 1;
	new_len = ft_mtrxlen(envp) + 1;
	nenvp = ft_calloc(new_len + 1, sizeof(envp));
	if (!nenvp)
		return (free_dpc(envp), NULL);
	envpcpy(envp, nenvp, &i);
	if (!nenvp)
		return (free_dpc(envp), NULL);
	nenvp[i] = ft_strdup(new_var);
	if (!nenvp[i])
		return (free_dpc(nenvp), free_dpc(envp), NULL);
	return (free_dpc(envp), nenvp);
}

// Checks whether the new Variable already exists, if so it overwrites it.
static bool	check_vardup(char **envp2, char *input)
{
	int		i;
	char	*new_var;

	i = 0;
	new_var = ft_substr(input, 0, ft_strlen(ft_strchr3(input, '+')) - 1);
	while (envp2[i])
	{
		if (ft_strnstr(envp2[i], new_var, ft_strlen(new_var)))
			return (free(new_var), true);
		i++;
	}
	return (free(new_var), false);
}

static void	append_var(char **envp2, char *var)
{
	size_t	i;
	char	*var_name;
	char	*tmp;

	i = 0;
	tmp = ft_strchr3(var, '+');
	var_name = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	free (tmp);
	while (envp2[i])
	{
		if (ft_strnstr(envp2[i], var_name, ft_strlen(var_name)))
		{
			tmp = ft_strdup(envp2[i]);
			free(envp2[i]);
			envp2[i] = ft_strjoin(tmp, ft_strchr2(var, '='));
			return (free(var_name), free(tmp));
		}
		i++;
	}
}

void	append_handle(char **envp2, char *var)
{
	if (check_vardup(envp2, var))
		append_var(envp2, var);
	else
		envp2 = add_var(envp2, var);
}
