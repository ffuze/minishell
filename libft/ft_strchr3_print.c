/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr3_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:46:10 by lemarino          #+#    #+#             */
/*   Updated: 2025/04/29 12:18:58 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Prints the string s until the first occurrence of the character c
void	ft_strchr3_print(const char *s, int c)
{
	char	chr;
	int		i;

	chr = (char)c;
	i = 0;
	while (s[i])
	{
		ft_printf("%c", s[i]);
		if (s[i] == chr)
			break;
		i++;
	}
}