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
