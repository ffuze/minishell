/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:30:17 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/11 11:58:21 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./index.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}

void	ft_ls()
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		char *argv[] = {"ls", NULL, NULL};
		execve("/bin/ls", argv, NULL);
		// return EXIT_SUCCESS;
	}
	else
		wait(NULL);
}

void	ft_ls_l()
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		char *argv[] = {"ls", "-l", NULL};
		execve("/bin/ls", argv, NULL);
		// return EXIT_SUCCESS;
	}
	else
		wait(NULL);
}

int main(/*int argc, char **argv*/)
{
	char	*input;

	input = malloc(sizeof(char *));
	while (1)
	{
		input = readline("powershell> ");
		if (!input)
			return EXIT_FAILURE;
		else if (!(*input))
			continue;
		else if (ft_strcmp(input, "ls") == 0)
			ft_ls();
		else if (ft_strcmp(input, "ls -l") == 0)
			ft_ls_l();
		else
			printf("Command not found: %s\n", input);
		if (ft_strcmp(input, "clear") == 0)
		{
			rl_clear_history();
			// execve();
			free(input);
		}
		else
			add_history(input);
	}
	return EXIT_SUCCESS;
}