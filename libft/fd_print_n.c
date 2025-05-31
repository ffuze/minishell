/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_print_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:08:39 by lemarino          #+#    #+#             */
/*   Updated: 2025/05/31 10:44:07 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fd_print_n(int fd, int n)
{
	char	*s;
	int		l;

	s = ft_itoa(n);
	l = ft_strlen(s);
	ft_putstr_fd(s, fd);
	free(s);
	return (l);
}
