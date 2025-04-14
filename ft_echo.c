/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:00:30 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/14 19:41:54 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

static int	handle_single_quotes(char *input, int i)
{
	size_t	x;

	i++;
	x = (size_t)i;
	while (input[x] != '\0' && input[x] != 39)
		x++;
	if (x == ft_strlen(input) && input[x] != 39)
	{
		printf(RED"\nUnclosed ");
		printf(YELLOW"double ");
		printf(GREEN"quotes ");
		printf(BLUE"were ");
		printf(MAGENTA"found");
		printf(RED".\n"NO_ALL);
		return (-1);
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
	size_t	x;

	i++;
	x = (size_t)i;
	while (input[x] && input[x] != 34)
		x++;
	if (x == ft_strlen(input) && input[x] != 34)
	{
		printf(RED"\nUnclosed ");
		printf(YELLOW"double ");
		printf(GREEN"quotes ");
		printf(BLUE"were ");
		printf(MAGENTA"found");
		printf(RED".\n"NO_ALL);
		return (-1);
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
	if (input[j] == '-' && input[j + 1] == 'n')
	{
		j++;
		while (input[j] == 'n')
		{
			j++;
			if (input[j] && input[j] != 'n' && input[j] != ' ')
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

// Actually prints the characters unless it finds unclosed quotes
static int	ft_echo2(char *input)
{
	int	i;

	i = 0;
	while (ft_isprint(input[i]))
	{
		if (input[i] == 39)
			i = handle_single_quotes(input, i);
		else if (input[i] == 34)
			i = handle_double_quotes(input, i);
		if (i < 0)
			break ;
		printf("%c", input[i]);
		i++;
	}
	return (i);
}

void	ft_echo(char **input)
{
	int	j;

	j = 1;
	j += check_flag(input[j]);
	while (input[j])
	{
		ft_echo2(input[j]);
		j++;
		if (input[j])
			printf(" ");
	}
	if (check_flag(input[1]) == 0)
		printf("\n");
}
// c2r1p5% echo -nnnnfn      "cef'we"
// -nnnnfn cef'we

// c2r1p5% echo -nnnnfn      hbjh"cef'we"bj
// -nnnnfn hbjhcef'webj

// c2r1p5% echo -n -n nnfn      hbjh"cef'we"bj
// nnfn hbjhcef'webj%                   

// c2r1p5% echo "-n" -n nnfn      hbjh"cef'we"bj
// nnfn hbjhcef'webj%                       

// c2r1p5% echo "-n" nnfn      hbjh"cef'we"bj 
// nnfn hbjhcef'webj%                        

// c2r1p5% echo  nnfn      hbjh"cef'we"bj 
// nnfn hbjhcef'webj

// c2r1p5% echo "-n nytjjkj" nnfn      hbjh"cef'we"bj
// -n nytjjkj nnfn hbjhcef'webj
