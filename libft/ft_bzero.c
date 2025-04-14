/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:22:15 by adegl-in          #+#    #+#             */
/*   Updated: 2024/11/26 12:44:05 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*int main()
{
	char str[50] = "GeeksForGeeks is for programming geeks.";
	printf("Before bzero(): %s\n", str);

	ft_bzero(str, 8*sizeof(char));

	printf("After bzero():  %s", str);
	return 0;
}*/
