/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex (copy).c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:49:14 by adegl-in          #+#    #+#             */
/*   Updated: 2025/02/10 14:21:17 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_xl_xu(unsigned int n, int uppercase)
{
	char			*base;
	char			res[17];
	int				i;
	int				count;

	count = 0;
	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	i = 0;
	if (n == 0)
		return (write(1, "0", 1));
	while (n > 0)
	{
		res[i++] = base[n % 16];
		n /= 16;
	}
	res[i] = '\0';
	count = i;
	while (--i >= 0)
		write(1, &res[i], 1);
	return (count);
}
