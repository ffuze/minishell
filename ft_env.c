#include "minishell.h"

// Prints all the environment variables
void	ft_env(char **envp2)
{
	int	i;

	i = 0;
	while(envp2[i])
		printf("%s\n", envp2[i++]);
}
// Dopo "unset PATH":
// bash: env: No such file or directory