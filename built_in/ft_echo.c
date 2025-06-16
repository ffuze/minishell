#include "../minishell.h"

static int	check_flag(char **cmd, int j)
{
	int	i;

	while (cmd[j])
	{
		i = 0;
		if (cmd[j][i] != '-' || cmd[j][i + 1] != 'n')
			break;
		i++;
		while (cmd[j][i] == 'n')
			i++;
		if (cmd[j][i] != '\0')
			break;
		j++;
	}
	return (j);
}

void	ft_echo(char **cmd)
{
	int	i;
	int	newline;

	newline = 1;
	i = check_flag(cmd, 1);
	if (i > 1)
		newline = 0;
	while (cmd[i] != NULL)
	{
		ft_printfd(1, "%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		ft_printfd(1, "\n");
}
