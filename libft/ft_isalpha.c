/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:59:03 by adegl-in          #+#    #+#             */
/*   Updated: 2024/11/26 12:45:01 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/*int main(void)
{
	printf("%d\n", ft_isalpha('f')); // Dovrebbe stampare 1
	printf("%d\n", ft_isalpha('F')); // Dovrebbe stampare 1
	printf("%d\n", ft_isalpha('1')); // Dovrebbe stampare 0
	return (0);
}*/