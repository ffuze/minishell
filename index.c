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
	// char	**envp2;
	t_msh	msh;
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
	clearflag = 0;
	msh.envp2 = ft_envp_dup(envp);// Deve stare fuori dal while()
	if (!msh.envp2)
		return(printf(RED"Failed envp2"NO_ALL), EXIT_FAILURE);
	while (1)
	{
		input = readline(BGMAGENTA"powershell> "NO_ALL);
		if (!input)
			return EXIT_FAILURE;
		else if (!(*input))
			continue;
		msh.tokens = tokenize(input);
		
		for (size_t i = 0; msh.tokens[i] != NULL; i++)
			printf("Token numero %zu: %s e' di tipo: %d++\n", i, msh.tokens[i]->value, msh.tokens[i]->type);
		if (!msh.tokens)
			continue ;
		if (msh.tokens[0] && ft_strcmp(msh.tokens[0]->value, "exit") == 0)
			return (free_dpc(msh.envp2), EXIT_SUCCESS);
		else if (ft_strcmp(msh.tokens[0]->value, "export") == 0)
		{
			ft_export(&msh);
			if (!msh.envp2)
				return(printf(RED"Failed envp2"NO_ALL), EXIT_FAILURE);
		}
		else if (msh.tokens[0] && ft_strcmp(msh.tokens[0]->value, "pwd") == 0)
			ft_pwd();
		else if (msh.tokens[0] && ft_strcmp(msh.tokens[0]->value, "env") == 0)
			ft_env(msh.envp2);
		else if ((ft_strcmp(msh.tokens[0]->value, "echo")) == 0)
			ft_echo(msh.tokens);
		else if (msh.tokens[0] && msh.tokens[0]->type == TOKEN_WORD
			&& ft_strcmp(msh.tokens[0]->value, "clear") == 0)
		{
			ft_clear(input);
			clearflag = 1;
		}
		else
			printf("Command not found: %s\n", input);
		if (!clearflag)
			add_history(input);
		free(input);
	}
	free_dpc(msh.envp2);
	return EXIT_SUCCESS;
}
