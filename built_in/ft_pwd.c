/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:10:24 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:32 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Prints the absolute path to the current directory.
int	ft_pwd(void)
{
	char	*dir_path;

	dir_path = malloc(PATH_MAX);
	if (!dir_path)
		return (perror("Operation failed"), 1);
	dir_path = getcwd(dir_path, PATH_MAX);
	if (!dir_path)
		return (perror("Operation failed"), 1);
	ft_printfd(1, "%s\n", dir_path);
	free(dir_path);
	return (0);
}
