/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:27:05 by adegl-in          #+#    #+#             */
/*   Updated: 2024/12/05 17:45:40 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	int		tot;

	tot = nmemb * size;
	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (tot / size != nmemb)
		return (NULL);
	ptr = malloc(tot);
	if (ptr == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

/*int main()
{
	size_t	n = 5;
	int *arr = ft_calloc(n, sizeof(int));
	if (!arr)
		printf("Non e' stato allocato niente in memoria");
	else
	{
		size_t i = 0;
		while (i < n)
		{
			printf("arr[%ld] = %d\n", i, arr[i]);
			i++;
			
		}
	}
	free(arr);
}*/