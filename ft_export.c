#include "minishell.h"

char	**ft_sortenvp(char	**envp)
{
	char	**sorted_envp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	sorted_envp = ft_calloc(ft_mtrxlen(envp) + 1, sizeof(char *));
	if (!sorted_envp)
		return (NULL);
}

void	print_declarex(char **envp2)
{
	int		i;
	char **sorted_envp;

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

void	ft_export(char **input, char **envp2)
{
	if (!input[1])
		print_declarex(envp2);
}
// nome della variabile non puo cominciare con un numero e deve avere solo char alfanumerici e/o '_'
// variabile non puo avere $ o | nel contenuto