/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:00:30 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/14 13:09:55 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

static int	handle_single_quotes(char *input, int i)
{
	size_t j;

	i++;
	j = (size_t)i;
	while (input[j] != '\0' && input[j] != 39)// il primo i++ era dopo quindi input[j] == 39 e quindi non entrava in questo while
		j++;
	if (j == ft_strlen(input) && input[j] != 39)
	{
		printf("Unclosed single quotes were found.");
		return (0);
	}
	while (input[i] != 39)
	{
		printf("%c", input[i]);
		i++;
	}
	printf("\nj = %zu\n", j);
	printf("ft_strlen(input) = %zu\n", ft_strlen(input));
	i++;
	return (i);
}

static int	handle_double_quotes(char *input, int i)
{
	size_t	j;

	j = (size_t)i;
	while (input[j] && input[j] != 34)
		j++;
	if (j == ft_strlen(input) && input[j] != 34)
	{
		printf("Unclosed double quotes were found.");
		return (0);
	}
	i++;
	while (input[i] != 34)
	{	
		printf("-------------------------------------\n");
		printf("%c", input[i]);
		i++;
	}
	i++;
	return (i);
}

void	ft_echo(char *input)
{
	int	i;

	i = 4;
	if ((input[i] > 32 && input[i] < 96) || (input[i] > 96 && input[i] < 127))
	{
		printf("\n");
		return ;
	}
	while (input && input[i] == ' ')
	{
		printf("-----------------------------------\n");
		i++;
	}
	while (ft_isprint(input[i]))
	{
		if (input[i] == 39) // '
			i = handle_single_quotes(input, i);
		else if (input[i] == 34) // "
			i = handle_double_quotes(input, i);
		if (i == 0)
			break ;
		printf("%c", input[i]);
		i++;
	}
	printf("\n");
}
