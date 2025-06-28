#include "../minishell.h"

// Prints the absolute path to the current directory.
void	ft_pwd()
{
	char	*dir_path;

	dir_path = malloc(PATH_MAX);
	if (!dir_path)
		return (perror("Operation failed"));
	dir_path = getcwd(dir_path, PATH_MAX);
	if (!dir_path)
		return (perror("Operation failed"));
	ft_printfd(1, "%s\n", dir_path);
	free(dir_path);
}
