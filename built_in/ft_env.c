#include "../minishell.h"

// Prints all the environment variables
void	ft_env(char **envp2)
{
	int	i;

	i = 0;
	while(envp2[i])
	{
		if (ft_strchr(envp2[i], '='))
			ft_printfd(1, "%s\n", envp2[i++]);
		else
			i++;
	}
}
