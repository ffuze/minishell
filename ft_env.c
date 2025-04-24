#include "minishell.h"

// Prints all the environment variables
void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
		printf("%s\n", envp[i++]);
}
// Dopo "unset PATH":
// bash: env: No such file or directory