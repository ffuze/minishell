#include "../minishell.h"

void	ft_exit(t_msh *msh, char *input)
{
	free_everything(*msh, input);
	free_output_redirection(msh);
	free_cmd_list(msh->cmds);
	exit(EXIT_SUCCESS);
}
