/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:04:11 by adegl-in          #+#    #+#             */
/*   Updated: 2025/06/04 19:29:20 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*s3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = ft_calloc((len1 + len2 + 1), sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		s3[i++] = *s1++;
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	return (s3);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*s3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = ft_calloc((len1 + len2 + 1), sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		s3[i++] = *s1++;
	while (*s2)
		s3[i++] = *s2++;
	s3[i] = '\0';
	free((char *)s1);
	return (s3);
}
