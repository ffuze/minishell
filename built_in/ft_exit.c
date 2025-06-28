#include "../minishell.h"

void	ft_exit(t_msh *msh)
{
	free_cmd_list(msh->cmds);
	free_everything(*msh);
	exit(EXIT_SUCCESS);
}
// limite exit status: 255