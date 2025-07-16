/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:53:04 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/16 16:52:53 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Substitutes the standard output with a file.
void	redirect_output(t_msh *msh, t_cmds *current)
{
	int		outfile_fd;

	if (!current->outfile || !current->outfile[0])
		return ;
	if (current->append_flag)
		outfile_fd = open(current->outfile, O_WRONLY | O_CREAT | \
														O_APPEND, 0644);
	else
		outfile_fd = open(current->outfile, O_WRONLY | O_CREAT | \
														O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		print_err(current->outfile, ": output file could not be opened.\n");
		free_cmd_list(msh->cmds);
		free_stuff(*msh);
		exit(1);
	}
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}
