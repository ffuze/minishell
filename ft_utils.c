/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:46:35 by adegl-in          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2025/04/23 11:03:07 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	skip_spaces(t_token *input, int i)
{
	while (input->value[i] && input->value[i] == ' ')
=======
=======
>>>>>>> master
/*   Updated: 2025/04/15 10:41:42 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./index.h"

int	skip_spaces(char *input, int i)
{
	while (input[i] && input[i] == ' ')
<<<<<<< HEAD
>>>>>>> master
=======
>>>>>>> master
		i++;
	return (i);
}