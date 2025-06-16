#include "../minishell.h"

/* int	identify_builtin_commands(t_msh *msh, char **split_input, char *input)
{
	if (ft_strcmp(msh->tokens[0]->value, "env") == 0)
		ft_env(msh->envp2);
	else if (ft_strcmp(msh->tokens[0]->value, "export") == 0)
	{
		ft_export(msh, split_input);
		if (!msh->envp2)
			return (-1);
	}
	else if (ft_strcmp(msh->tokens[0]->value, "unset") == 0)
	{
		ft_unset(msh, split_input);
		if (!msh->envp2)
			return (-1);
	}
	else if (ft_strcmp(msh->tokens[0]->value, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(msh->tokens[0]->value, "cd") == 0)
		ft_cd(msh, split_input);
	else if (ft_strcmp(msh->tokens[0]->value, "echo") == 0)
		ft_echo(split_input);
	else if (ft_strcmp(msh->tokens[0]->value, "clear") == 0)
	{
		ft_clear(input);
		return (2);
	}
	else if (ft_strcmp(msh->tokens[0]->value, "exit") == 0)
		return (1);
	else
		return (0);
} */
