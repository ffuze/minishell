#include "../minishell.h"

void	ft_exit(t_msh *msh)
{
	free_everything(*msh);
	free_cmd_list(msh->cmds);
	exit(EXIT_SUCCESS);
}
