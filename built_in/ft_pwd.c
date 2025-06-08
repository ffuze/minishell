#include "../minishell.h"

// Check if the command line has got a redirection/append/heredoc: if it does,
// execute the command in the found token, otherwise just execute the command
// normally.
// int	check_token_presence(t_msh *msh)
// {

// }

// Prints the absolute path to the current directory.
void	ft_pwd()
{
	// int		i;
	char	*dir_path;

	// i = 0;
	dir_path = malloc(PATH_MAX);
	if (!dir_path)
		return (perror("Operation failed"));
	dir_path = getcwd(dir_path, PATH_MAX);
	if (!dir_path)
		return (perror("Operation failed"));
	printf("%s\n", dir_path);
	free(dir_path);
}
