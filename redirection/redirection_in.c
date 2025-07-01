/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:52:55 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/01 21:24:43 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Substitutes the standard input with a file.
void	redirect_input(t_msh *msh, t_cmds *current)
{
	int		infile_fd;

	if (!current->infile)
		return ;
	infile_fd = open(current->infile, O_RDONLY, 0644);
	if (infile_fd < 0)
	{
		print_err(current->infile, ": could not be opened.\n");
		free_cmd_list(msh->cmds);
		free_stuff(*msh);
		exit(1);
	}
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
}
