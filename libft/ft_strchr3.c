/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:46:10 by lemarino          #+#    #+#             */
/*   Updated: 2025/05/06 15:13:24 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates memory and return a duplicate of the string s up until the first c
char	*ft_strchr3(const char *s, int c)
{
	char	*nstr;
	char	chr;
	int		i;
	int		j;

	chr = (char)c;
	i = 0;
	j = 0;
	while (s[i] && s[i] != chr)
		i++;
	nstr = ft_calloc(i + 2, sizeof(char));
	if (!nstr)
		return (NULL);
	while (j <= i)
	{
		nstr[j] = s[j];
		j++;
	}
	return (nstr);
}

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