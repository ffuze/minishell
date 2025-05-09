#include "minishell.h"

// Prints all the environment variables
void	ft_env(t_msh *msh, char **envp2)
{
	int	i;

	i = 0;
	if (msh->env_existence == true)
	{
		while(envp2[i])
			printf("%s\n", envp2[i++]);
	}
	else
	{
		ft_putstr_fd("bash: env: No such file or directory\n", 2);
		msh->exit_status = 127;
	}
}
// Dopo "unset PATH":
// bash: env: No such file or directory
// non deve mostrare variabili vuote