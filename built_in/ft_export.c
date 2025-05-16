#include "../minishell.h"

void	str_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

// Returns a copy of ENVP sorted according to ASCII.
char	**ft_sortenvp(char	**envp)
{
	char	**sorted_envp;
	size_t	i;
	size_t	l;
	size_t	k;

	i = 0;
	l = ft_mtrxlen(envp);
	k = 0;
	sorted_envp = ft_envp_dup(envp);
	if (!sorted_envp)
		return (NULL);
	while (k++ < l)
	{
		while (sorted_envp[i + 1])
		{
			if (ft_strcmp(sorted_envp[i], sorted_envp[i + 1]) > 0)
				str_swap(&sorted_envp[i], &sorted_envp[i + 1]);
			i++;
		}
		i = 0;
	}
	return (sorted_envp);
}

// Prints Environment Vars in ASCII order with their value in double quotes.
void	print_declarex(char **envp2)
{
	int		i;
	char	*tmp;
	char	**sorted_envp;

	i = 0;
	sorted_envp = ft_sortenvp(envp2);
	if (!sorted_envp)
		return ;
	while (sorted_envp[i])
	{
		ft_printf("declare -x ");
		tmp = ft_strchr3(sorted_envp[i], '=');
		if (!tmp)
			return ;
		ft_printf("%s", tmp);
		free(tmp);
		if (ft_strchr(sorted_envp[i], '='))
			ft_printf("\"%s\"", ft_strchr2(sorted_envp[i], '='));
		ft_printf("\n");
		i++;
		
	}
	free_dpc(sorted_envp);
}
//-------------------------------------------------------------------------------//

// Copies the old envp to the newly allocated one.
void	envpcpy(char **envp2, char **nenvp, size_t *i)
{
	while (envp2[*i])
	{
		nenvp[*i] = ft_strdup(envp2[*i]);
		if (!nenvp[*i])
			{
				free_dpc(nenvp);
				return ;
			}	
		(*i)++;
	}
}

// Adds the new variables to the Environment.
char	**add_var(char **envp, char *new_var)
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
//---------------------------------------------------------------------------//

// Checks whether the new Variable already exists, if so it overwrites it.
bool	check_vardup(char **envp2, char *input)
{
	int		i;
	char	*new_var;

	i = 0;
	new_var = ft_strchr3(input, '=');
	while (envp2[i])
	{
		if (ft_strnstr(envp2[i], new_var, ft_strlen(new_var)))
		{
			free(envp2[i]);
			envp2[i] = ft_strdup(input);
			return (free(new_var), true);
		}
		i++;
	}
	return (free(new_var), false);
}

// Checks whether the new Variable's name is acceptable.
// A var's name cannot start by number or symbol and cannot cointain symbols.
int	var_name_check(t_msh *msh, char *new_var)
{
	int		j;
	char	chr;
	char	*var_name;

	j = 0;
	if (!ft_isalpha(new_var[0]) && new_var[0]!= '_')
	{
		msh->exit_status = 1;
		return (false);
	}
	var_name = ft_strchr3(new_var, '=');
	while (var_name[j])
	{
		chr = var_name[j++];
		if ((chr < 'A' || chr > 'Z') && (chr < 'a' || chr > 'z') \
				&& (chr < '0' || chr > '9') && chr != '_' && chr != '=')
		{
			msh->exit_status = 1;
			return (free(var_name), false);
		}
	}
	return (free(var_name), true);
}
//-----------------------------------------------------------------------------//

void	ft_export(t_msh *msh, char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
		print_declarex(msh->envp2);
	else
	{
		while (cmd[i])
		{
			if (!var_name_check(msh, cmd[i]))
				ft_printf(RED"export: `%s': not a valid identifier\n"NO_ALL, \
														cmd[i]);
			else if (check_vardup(msh->envp2, cmd[i]))
				;
			else
				msh->envp2 = add_var(msh->envp2, cmd[i]);
			i++;
		}
	}
}
