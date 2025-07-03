/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:49:03 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/03 11:36:03 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// function that saves the positions of the commands that need
// to be saved in the cmds list
int	*count_commands(t_msh *msh)
{
	int	count;
	int	*positions;
	int	i;

	count = 0;
	i = 0;
	positions = malloc(50 * sizeof(int));
	ft_printf("valore di tokens[%d]: %s\n", i, msh->tokens[i]->value);
	if (!positions || !msh->tokens || !msh->tokens[i])
		return (NULL);
	while (msh->tokens[i])
	{
		if (msh->tokens[i]->type != TOKEN_RE_INPUT
			&& msh->tokens[i]->type != TOKEN_RE_OUTPUT
			&& msh->tokens[i]->type != TOKEN_PIPE)
			positions[count++] = i;
		i++;
	}
	return (positions);
}

// function that inserts all the found commands into an array
void	tokenize_commands(t_msh *msh)
{
	int	*positions;
	int	count;
	int	i;

	count = 0;
	i = 0;
	positions = count_commands(msh);
	if (!positions)
		return ;
	if (!msh->cmds)
		return ;
	while (count > 0 && positions[count] != 0)
	{
		msh->cmds[count].cmd = &msh->tokens[positions[count]]->value;
		count++;
	}
	free(positions);
}
