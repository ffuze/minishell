/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:35:38 by adegl-in          #+#    #+#             */
/*   Updated: 2024/11/20 15:35:38 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dups;

	i = 0;
	while (s[i] != '\0')
		i++;
	dups = malloc((i + 1) * sizeof(char));
	if (dups == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dups[i] = s[i];
		i++;
	}
	dups[i] = '\0';
	return (dups);
}
/*int main()
{
	const char *src = "mommy reyna";
	char *dst = ft_strdup(src);
	printf("Stringa originale: %s\n", src);
	printf("Stringa duplicata: %s\n", dst);
	printf("Indirizzo di memoria della stringa allocata: %p", &dst);
	free(dst);
}*/
