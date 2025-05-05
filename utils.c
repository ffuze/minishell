#include "./minishell.h"

int	skip_spaces(t_token *input, int i)
{
	while (input->value[i] && input->value[i] == ' ')
		i++;
	return (i);
}

// Duplicates the pointer to Environment Variables
char	**ft_envp_dup(char **envp)
{
	char	**envp2;
	int		i;

	i = 0;
	size_t	l;
	l = ft_mtrxlen(envp);
	envp2 = ft_calloc((l + 1), sizeof(char *));
	if (!envp2)
		return (NULL);
	while (envp[i])
	{
		envp2[i] = ft_strdup(envp[i]);
		if (!envp2[i])
			return (free_dpc(envp2), NULL);
		i++;
	}
	return (envp2);
}
