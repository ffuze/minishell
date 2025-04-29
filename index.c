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
	// char	**split_input;
	t_token	**tokens;
	int		clearflag;

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
	clearflag = 0;
	while (1)
	{
		input = readline(BGMAGENTA"powershell> "NO_ALL);
		if (!input)
			return EXIT_FAILURE;
		else if (!(*input))
			continue;
		tokens = tokenize(input);
		for (size_t i = 0; tokens[i] != NULL; i++)
			printf("Token numero %zu: %s++\n", i, tokens[i]->value);
		if (!tokens)
			continue ;
		// split_input = ft_split(input, ' ');
		if (tokens[0] && ft_strcmp(tokens[0]->value, "exit") == 0)
			return EXIT_SUCCESS;
		else if (ft_strcmp(tokens[0]->value, "export") == 0)
			ft_export(tokens, envp2);
		else if (tokens[0] && ft_strcmp(tokens[0]->value, "pwd") == 0/*, tokens[0]->type == TOKEN_WORD*/)
			ft_pwd();
		else if (tokens[0] && ft_strcmp(tokens[0]->value, "env") == 0)
			ft_env(envp2);
		// else if (ft_strcmp(split_input[0], "ls") == 0)
		// 	ft_ls(split_input);
		// else if (ft_strcmp(split_input[0], "ls -l") == 0)
		// 	ft_ls_l();
		// else if ((ft_strcmp(split_input[0], "echo")) == 0)
		// 	ft_echo(split_input);
		else if (tokens[0] && tokens[0]->type == TOKEN_WORD
			&& ft_strcmp(tokens[0]->value, "clear") == 0)
		{
				ft_clear(input);
				clearflag = 1;
		}
		else
			printf("Command not found: %s\n", input);
		if (!clearflag)
			add_history(input);
		free(input);
		// free_dpc(split_input);
	}
	free_dpc(envp2);
	return EXIT_SUCCESS;
}
