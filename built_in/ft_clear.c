#include "../minishell.h"

void	ft_clear(t_msh *msh, char *input)
{
	int	pid;

	pid = fork();
	msh->clearflag = 1;
	if (pid == 0)
	{
		reset_child_signals();
		char *argv[] = { "clear", NULL };
		execve("/usr/bin/clear", argv, __environ);
		rl_clear_history();
		free(input);	
	}
	else
		wait(NULL);
}
