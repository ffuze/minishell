/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:34:07 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/16 11:34:04 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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