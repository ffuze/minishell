#include "../minishell.h"

int is_valid_number(char *str)
{
    int j;

	j = 0;
    if (str[0] == '-' || str[0] == '+')
        j = 1;
    if (!str[j])
        return (0);
    while (str[j])
    {
        if (str[j] < '0' || str[j] > '9')
            return (0);
        j++;
    }
    return (1);
}

int all_args_int(char **args)
{
    int i = 0;
    
    while (args[i])
    {
        if (!is_valid_number(args[i]))
            return (0);
        i++;
    }
    return (1);
}

void ft_exit(t_msh *msh, char **args)
{
    int exit_status;
    
	exit_status = 0;
    if (ft_mtrxlen(args) > 2)
    {
        ft_printfd(2, RED"pokeshell: exit: too many arguments\n"NO_ALL);
		msh->exit_status = 1;
        return ;
    }
    if (args[1])
    {
        if (!is_valid_number(args[1]))
        {
            ft_printfd(2, "pokeshell: exit: %s: numeric argument required\n", \
                                                                     args[1]);
            exit_status = 2;
            free_cmd_list(msh->cmds);
            free_everything(*msh);
            exit(exit_status);
        }
        exit_status = ft_atoi(args[1]);
        exit_status = exit_status % 256;
        if (exit_status < 0)
            exit_status = 256 + exit_status;
    }
    free_cmd_list(msh->cmds);
    free_everything(*msh);
    exit(exit_status);
}
