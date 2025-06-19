#include "../minishell.h"

// Closes all file descriptors and liberates the allocated memory
void	liberate_fdmatrix(int **fd_mrx, int pipe_count)
{
	int	j;

	j = 0;
	if (!fd_mrx)
		return ;
	while (j <= pipe_count)
	{
		close(fd_mrx[j][0]);
		close(fd_mrx[j][1]);
		free(fd_mrx[j]);
		j++;
	}
	free(fd_mrx);
}

// Creates an FD for each pipe in the command line.
int	**fd_matrix_creator(int pipe_count)
{
	int	**fd_matrix;
	int	i;

	i = 0;
	fd_matrix = ft_calloc((pipe_count + 1), sizeof(int *));
	if (!fd_matrix)
		exit(1);//////////////////////////////////////////
	while (i < (pipe_count))
	{
		fd_matrix[i] = ft_calloc(2, sizeof(int));
		if (!fd_matrix[i])
		{
			liberate_fdmatrix(fd_matrix, i);
			exit(1);
		}
		i++;
	}
	return (fd_matrix);
}
