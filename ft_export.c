#include "minishell.h"

void	str_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

// Returns a copy of ENVP sorted according to ASCII
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

// Prints Environment Vars in ASCII order with their value in double quotes
void	print_declarex(char **envp2)
{
	int		i;
	char	**sorted_envp;

	i = 0;
	sorted_envp = ft_sortenvp(envp2);
	if (!sorted_envp)
		return ;
	while (sorted_envp[i])
	{
		ft_printf("declare -x ");
		ft_strchr3_print(sorted_envp[i], '=');
		printf("\"%s\"\n", ft_strchr2(sorted_envp[i], '='));
		i++;
	}
	free_dpc(sorted_envp);
}

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

char	**add_var(t_msh *msh)
{
	size_t		n_vars;
	size_t		i;
	char		**nenvp;

	i = 0;
	n_vars = 0;
	while (msh->tokens[n_vars])
		n_vars++;
	n_vars += ft_mtrxlen(msh->envp2);
	nenvp = ft_calloc(n_vars + 1, sizeof(msh->envp2));
	if (!nenvp)
		return (free_dpc(msh->envp2), NULL);
	envpcpy(msh->envp2, nenvp, &i);
	if (!nenvp)
		return (free_dpc(msh->envp2), NULL);
	while (i < n_vars)
	{
		nenvp[i] = ft_strdup(msh->envp2[i]);
		if (!nenvp[i])
			return (free_dpc(nenvp), free_dpc(msh->envp2), NULL);
		i++;
	}
	return (free_dpc(msh->envp2), nenvp);
}

void	ft_export(t_msh *msh)
{
	if (!msh->tokens[1])
		print_declarex(msh->envp2);
	if (msh->tokens[1])
		msh->envp2 = add_var(msh);
		// printf("dededede\n");//////////////////
}
// nome della variabile deve avere solo char alfanumerici e/o '_'
// variabile non puo avere $ o | nel contenuto