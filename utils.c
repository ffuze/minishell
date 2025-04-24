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
	envp2 = NULL;
	while (envp[i])
	{
		envp2 = ft_realloc(envp2, ((i + 1) * sizeof(char *)),
											((i + 2) * sizeof(char *)));
		if (!envp2)
			return (NULL);
		envp2[i] = ft_strdup(envp[i]);
		if (!envp2[i])
			return (free_dpc(envp2), NULL);
		i++;
	}
	return (envp2);
}
