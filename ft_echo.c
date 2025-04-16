/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:00:30 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/16 15:43:33 by adegl-in         ###   ########.fr       */
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

static int	handle_double_quotes(t_token *input, int i)
{
	size_t	j;

	i++;
	j = (size_t)i;
	while (input->value[i] && input->value[i] != 34)
		j++;
	if (j == ft_strlen(input) && input->value[i] != 34)
	{
		printf("\nUnclosed double quotes were found.");
		return (0);
	}
	while (input->value[i] != 34)
	{
		printf("%c", input->value[i]);
		i++;
	}
	i++;
	return (i);
}

// Verifies whether the "-n" flag is to be applied,
//  no matter how many letters are after the sign.
static int	check_flag(t_token *input)
{
	int	j;

	j = 0;
	while (input->value[j] && input->value[j] == ' ')
		j++;
	if (input->value[j] == '-' && input->value[j + 1] == 'n')
	{
		j++;
		while (input->value[j] == 'n')
		{
			j++;
			if (input->value[j] != 'n' && input->value[j] != ' ')
				return (0);
		}
	}
	else
		return (0);
	return (j);
}

// Actually prints the characters unless it finds unclosed quotes
static int	ft_echo2(t_token *input, int i)
{
	while (input->value[i] && input->value[i] == ' ')
		i++;
	while (ft_isprint(input->value[i]))
	{
		if (input->value[i] == 39)
			i = handle_single_quotes(input->value[i], i);
		else if (input->value[i] == 34)
			i = handle_double_quotes(input->value[i], i);
		if (i == 0)
			break ;
		printf("%c", input->value[i]);
		i++;
	}
	return (i);
}

void	ft_echo(t_token *input)
{
	int	i;

	i = 4;
	if ((input->value[i] > 32 && input->value[i] < 96)
		|| (input->value[i] > 96 && input->value[i] < 127))
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
