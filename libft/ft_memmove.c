/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:43:15 by adegl-in          #+#    #+#             */
/*   Updated: 2024/11/27 12:45:48 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptrdest;
	const unsigned char	*ptrsrc;

	ptrdest = (unsigned char *)(dest);
	ptrsrc = (const unsigned char *)(src);
	if (!dest && !src)
		return (NULL);
	if (ptrsrc < ptrdest)
	{
		while (n--)
			ptrdest[n] = ptrsrc[n];
	}
	else
	{
		while (n--)
			*ptrdest++ = *ptrsrc++;
	}
	return (dest);
}

/*int main()
{
	char dest[20] = "porco giuda";
	const char src[] = "censura";

	printf("Before memmove():  %s\n", dest);

	ft_memmove(dest, src, sizeof(src));

	printf("After memmove():  %s", dest);

	return 0;
}*/