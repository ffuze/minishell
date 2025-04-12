/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:30:17 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/11 17:13:25 by adegl-in         ###   ########.fr       */
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

void	ft_clear(char *input)
{
	char *argv[] = { "clear", NULL };
	execve("/usr/bin/clear", argv, __environ);
	rl_clear_history();
	free(input);
}

void	ft_handler()
{
	write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(/*int argc, char **argv*/)
{
	struct sigaction sa;
	char	*input;

	sa.sa_handler = ft_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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
		else if (ft_strcmp(input, "exit") == 0)
			return EXIT_SUCCESS;
		else
			printf("Command not found: %s\n", input);
		if (ft_strcmp(input, "clear") == 0)
			ft_clear(input);
		else
			add_history(input);
	}
	return EXIT_SUCCESS;
}
