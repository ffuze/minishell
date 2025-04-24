#include "./minishell.h"

// void	ft_ls()
// {
// 	int	pid;
	
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		char *argv[] = {"ls", NULL, NULL};
// 		execve("/bin/ls", argv, NULL);
// 	}
// 	else
// 		wait(NULL);
// }

// void	ft_ls_l()
// {
// 	int	pid;
	
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		char *argv[] = {"ls", "-l", NULL};
// 		execve("/bin/ls", argv, NULL);
// 	}
// 	else
// 		wait(NULL);
// }

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

int main(int ac, char *av[], char **envp)
{
	struct	sigaction sa;
	char	*input;
	char	**envp2;
	char	**split_input;

	(void)ac;
	av = NULL;
	sa.sa_handler = ft_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	envp2 = ft_envp_dup(envp);
	input = malloc(sizeof(char *));
	while (1)
	{
		input = readline(BGMAGENTA"powershell> "NO_ALL);
		if (!input)
			return EXIT_FAILURE;
		else if (!(*input))
			continue;
		split_input = ft_split(input, ' ');
		if (ft_strcmp(split_input[0], "exit") == 0 && !split_input[1])
			return EXIT_SUCCESS;
		// else if (ft_strcmp(split_input[0], "export") == 0)
		// 	ft_export();
		else if (ft_strcmp(split_input[0], "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(split_input[0], "env") == 0)
			ft_env(envp2);
		// else if (ft_strcmp(split_input[0], "ls") == 0)
		// 	ft_ls(split_input);
		// else if (ft_strcmp(split_input[0], "ls -l") == 0)
		// 	ft_ls_l();
		// else if ((ft_strcmp(split_input[0], "echo")) == 0)
		// 	ft_echo(split_input);
		else
			printf("Command not found: %s\n", input);
		if (ft_strcmp(split_input[0], "clear") == 0 && !split_input[1])
			ft_clear(input);
		else
			add_history(input);
		free(input);
		free_dpc(split_input);
	}
	free_dpc(envp2);
	return EXIT_SUCCESS;
}
