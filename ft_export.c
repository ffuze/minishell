#include "minishell.h"

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
void	print_declarex(t_msh *msh, char **envp2)
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
	msh->exit_status = 0;
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
char	**add_var(t_msh *msh)
{
	size_t	n_vars;
	size_t	i;
	size_t	j;
	char	**nenvp;

	n_vars = 0;
	i = 0;
	j = 1;
	while (msh->tokens[n_vars])
		n_vars++;
	n_vars += ft_mtrxlen(msh->envp2);
	nenvp = ft_calloc(n_vars, sizeof(msh->envp2));
	if (!nenvp)
		return (free_dpc(msh->envp2), NULL);
	envpcpy(msh->envp2, nenvp, &i);
	if (!nenvp)
		return (free_dpc(msh->envp2), NULL);
	while (i < n_vars - 1)
	{
		nenvp[i] = ft_strdup(msh->tokens[j++]->value);
		if (!nenvp[i++])
			return (free_dpc(nenvp), free_dpc(msh->envp2), NULL);
	}
	return (free_dpc(msh->envp2), nenvp);
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

// Checks whether the new Variable is acceptable or already exists,
//  then acts accordingly.
void	newvar_check(t_msh *msh)
{
	int		i;
	char	chr;

	i = 1;
	msh->exit_status = 0;
	while (msh->tokens[i])
	{
		chr = msh->tokens[i]->value[0];
		if ((chr < 65 || chr > 90) && (chr < 97 || chr > 122) && chr != '_')
			{
				ft_printf(RED"bash: export: `%s': not a valid identifier\n"\
												NO_ALL,msh->tokens[i]->value);
				msh->exit_status = 1;
				return ;
			}
		else if (check_vardup(msh->envp2, msh->tokens[i]->value))
			return ;
		else
			msh->envp2 = add_var(msh);
		i++;
	}
}
//-----------------------------------------------------------------------------//

void	ft_export(t_msh *msh)
{
	if (!msh->tokens[1])
		print_declarex(msh, msh->envp2);
	if (msh->tokens[1])
		newvar_check(msh);
}
// variabile non puo avere $ o | nel contenuto