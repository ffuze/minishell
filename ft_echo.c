/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:00:30 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/14 16:53:55 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

static int	handle_single_quotes(char *input, int i)
{
	size_t	j;

	i++;
	j = (size_t)i;
	while (input[j] != '\0' && input[j] != 39)
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
	i++;
	return (i);
}

static int	handle_double_quotes(char *input, int i)
{
	size_t	j;

	i++;
	j = (size_t)i;
	while (input[j] && input[j] != 34)
		j++;
	if (j == ft_strlen(input) && input[j] != 34)
	{
		printf("\nUnclosed double quotes were found.");
		return (0);
	}
	while (input[i] != 34)
	{
		printf("%c", input[i]);
		i++;
	}
	i++;
	return (i);
}

// Verifies whether the "-n" flag is to be applied,
//  no matter how many letters are after the sign.
static int	check_flag(char *input)
{
	int	j;

	j = 0;
	while (input && input[j] == ' ')
		j++;
	if (input[j] == '-' && input[j + 1] == 'n')
	{
		j++;
		while (input[j] == 'n')
		{
			j++;
			if (input[j] != 'n' && input[j] != ' ')
				return (0);
		}
	}
	else
		return (0);
	return (j);
}

// Actually prints the characters unless it finds unclosed quotes
static int	ft_echo2(char *input, int i)
{
	while (input && input[i] == ' ')
		i++;
	while (ft_isprint(input[i]))
	{
		if (input[i] == 39)
			i = handle_single_quotes(input, i);
		else if (input[i] == 34)
			i = handle_double_quotes(input, i);
		if (i == 0)
			break ;
		printf("%c", input[i]);
		i++;
	}
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
	i += check_flag(input + 4);
	i = ft_echo2(input, i);
	if (!check_flag(input + 4))
		printf("\n");
}
// evitare anche ';'(59) e '\'(92) in assenza di virgolette o apici?
// '\' da ignorare completamente
// stampare fino a ';'? 
