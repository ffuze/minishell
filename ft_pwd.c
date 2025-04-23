#include "minishell.h"

// Returns the absolute path to the current directory.
void	ft_pwd()
{
	int		i;
	char	*dir_path;

	i = 0;
	dir_path = malloc(PATH_MAX);
	if (!dir_path)
		return (perror("Operation failed"));
	dir_path = getcwd(dir_path, PATH_MAX);
	if (!dir_path)
		return (perror("Operation failed"));
	printf("%s\n", dir_path);
	free(dir_path);
}