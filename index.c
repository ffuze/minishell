/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:30:17 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/14 12:39:21 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./index.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_ls()
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		char *argv[] = {"ls", NULL, NULL};
		execve("/bin/ls", argv, NULL);
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
	}
	else
		wait(NULL);
}

void	ft_clear(char *input)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		char *argv[] = { "clear", NULL };
		execve("/usr/bin/clear", argv, __environ);
		rl_clear_history();
		free(input);	
	}
	else
		wait(NULL);
}

void	ft_handler(int signum)
{
	if (signum == SIGKILL)
		printf("ho intercettato un sigkill skibidi sigma\n");
	write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(/*int argc, char **argv*/)
{
	// char	*path = getenv("PATH");
	// char	**dir;
	// char	*all_paths;
	struct	sigaction sa;
	char	*input;

	// dir = ft_split(path, ':');
	// all_paths = malloc(sizeof(char));
	sa.sa_handler = ft_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	input = malloc(sizeof(char *));
	// for (size_t i = 0; i < ft_strlen(dir[i]); i++)
	// 		printf("%s\n", dir[i]);
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
		else if ((ft_strncmp(input, "echo ", 5)) == 0 || (ft_strcmp(input, "echo")) == 0)
			ft_echo(input);
		else
			printf("Command not found: %s\n", input);
		if (ft_strcmp(input, "clear") == 0)
			ft_clear(input);
		else
			add_history(input);
	}
	return EXIT_SUCCESS;
}
