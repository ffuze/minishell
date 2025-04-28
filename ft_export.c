#include "minishell.h"

// Returns a copy of ENVP sorted alphanumerically
char	**ft_sortenvp(char	**envp)
{
	char	**sorted_envp;
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	tmp = envp[i];
	sorted_envp = ft_calloc(ft_mtrxlen(envp) + 1, sizeof(char *));
	if (!sorted_envp)
		return (NULL);
	while (sorted_envp[k])
	{
		while (envp[i][j] && envp[i][j] != '=')// #################################
		{
			while (envp[i + 1] && tmp[j] < envp[i + 1][j])
				i++;
			tmp = envp[i];
			i = 0;
			j++;
		}
		sorted_envp[k] = tmp;
		k++;
		j = 0;
	}
	return (sorted_envp);
}

// Prints Environment Vars in alphanumeric order
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
		printf("declare -x ");
		printf("%s\n", sorted_envp[i]);
		i++;
	}
}

void	ft_export(char *input, char **envp2)
{
	if (!input[1])
		print_declarex(envp2);
}
// nome della variabile non puo cominciare con un numero e deve avere solo char alfanumerici e/o '_'
// variabile non puo avere $ o | nel contenuto