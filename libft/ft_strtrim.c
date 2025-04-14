/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:21:35 by adegl-in          #+#    #+#             */
/*   Updated: 2024/11/21 12:21:36 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

size_t	is_c_in_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*strtrim;

	start = 0;
	end = 0;
	if (!s1 || !set)
		return (NULL);
	while (is_c_in_set(s1[start], set))
		start++;
	while (s1[end] != '\0')
		end++;
	while (end > start && is_c_in_set(s1[end - 1], set))
		end--;
	strtrim = malloc((end - start + 1) * sizeof(char));
	if (!strtrim)
		return (NULL);
	i = 0;
	while (start < end)
		strtrim[i++] = s1[start++];
	strtrim[i] = '\0';
	return (strtrim);
}

/*int	main()
{
	char const *s1 = "abcvalo-rantabc";
	char const *set = "bca";
	char *trim = ft_strtrim(s1, set);
	printf("Stringa trimmata: %s", trim);
	free(trim);
}*/
