/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_matrix_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:05:28 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/06 18:11:26 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Closes all file descriptors and liberates the allocated memory
void	liberate_fdmatrix(int **fd_mrx, int pipe_number)
{
	int	j;

	j = 0;
	if (!fd_mrx)
		return ;
	while (j < pipe_number)
	{
		close(fd_mrx[j][0]);
		close(fd_mrx[j][1]);
		free(fd_mrx[j]);
		j++;
	}
	free(fd_mrx);
}

// Creates an FD for each pipe in the command line.
int	**fd_matrix_creator(int pipe_number)
{
	int	**fd_matrix;
	int	i;

	i = 0;
	fd_matrix = ft_calloc((pipe_number + 1), sizeof(int *));
	if (!fd_matrix)
		exit(1);
	while (i < (pipe_number))
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
