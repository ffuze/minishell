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

int main(int ac/* , char *av[] */, char **envp)
{
	struct	sigaction sa;
	char	*input;
	t_msh	msh;
	int		clearflag;
    char    **split_input; 
	int j;
	int redirect_found;

	redirect_found = 0;
	j = 0;
	(void)ac;
	// av = NULL;
	// msh.infile = NULL;
	// msh.outfile = NULL;
	sa.sa_handler = ft_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
 	// sigaction(SIGTERM, &sa, NULL);
	// sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	clearflag = 0;
	
	msh.envp2 = ft_envp_dup(envp);
	if (!msh.envp2)
		return(printf(RED"Failed envp2"NO_ALL), EXIT_FAILURE);
	while (1)
	{
		msh.cmds = crealista();///////////// Creazione della lista temporanea
		msh.exit_status = 0;
		// funzione per aggiornare ogni volta il path da stampare accanto a powershell
		input = readline(BGMAGENTA"powershell> "NO_ALL);
		if (!input)
		{
			if (msh.tokens)
				free_tokens(msh.tokens);
			free_dpc(msh.envp2);
			return (EXIT_FAILURE);
		}
		else if (!(*input))
		{
			free(input);
			continue;
		}
		split_input = ft_split(input, ' ');///////////////////////////
		msh.tokens = tokenize(&msh, input);
		if (msh.tokens && msh.tokens[0])
        {
            freeList(msh.cmds);
            msh.cmds = NULL;
            insert_commands_to_list(&msh);
            ft_printf(BLUE"Commands in list:\n"NO_ALL);
            printList(msh.cmds);
        }
		while (msh.tokens[j])
		{
			if (msh.tokens[j]->type == TOKEN_RE_OUTPUT || msh.tokens[j]->type == TOKEN_RE_INPUT)
			{
				execute_redirection(&msh, msh.tokens, j);
				redirect_found = 1;
				break;
			}
		}
		if (!redirect_found)
			pipe_check(&msh);
		for (size_t i = 0; msh.tokens && msh.tokens[i] != NULL; i++)
			printf("Token numero %zu: %s e' di tipo: %d++\n", i, msh.tokens[i]->value, msh.tokens[i]->type);//////////////
		ft_printf("Number of pipes: %d\n", msh.pipe_count);/////////////////

		// I want to create another string where to put the first position of the token,
		// so that I can remove the quotes from the command in order to make it recognizable
		// to the controls that are right after here, and then transfer the temp string back
		// to the tokens variable and keep working with it for the rest ot the time
			// while (msh.tokens[0])
		// {

		// }
		if (!msh.tokens || !msh.tokens[0])
		{
			free(input);
			free_dpc(split_input);
			continue ;
		}
		if (msh.tokens[0] && ft_strcmp(msh.tokens[0]->value, "exit") == 0)
		{
			freeList(msh.cmds);////////////////////////////////
			free_everything(msh, split_input, input);
			return (EXIT_SUCCESS);
		}
		else if (ft_strcmp(msh.tokens[0]->value, "export") == 0)
		{
			ft_export(&msh, split_input);
			if (!msh.envp2)
			{
				free_everything(msh, split_input, input);
				return (ft_putstr_fd(RED"Failed envp2"NO_ALL, 2), EXIT_FAILURE);
			}
		}
		else if (ft_strcmp(msh.tokens[0]->value, "unset") == 0)
		{
			ft_unset(&msh, split_input);
			if (!msh.envp2)
			{
				free_everything(msh, split_input, input);
				return(ft_putstr_fd(RED"Failed envp2"NO_ALL, 2), EXIT_FAILURE);
			}
		}
		else if (msh.tokens[0] && ft_strcmp(msh.tokens[0]->value, "pwd") == 0)
			ft_pwd();
		else if (msh.tokens[0] && ft_strcmp(msh.tokens[0]->value, "env") == 0)
			ft_env(msh.envp2);
		else if (msh.tokens[0] && ft_strcmp(msh.tokens[0]->value, "cd") == 0)
			ft_cd(&msh, split_input);
		else if ((ft_strcmp(msh.tokens[0]->value, "echo")) == 0)
			ft_echo(split_input);
		else if (msh.tokens[0] && ft_strcmp(msh.tokens[0]->value, "clear") == 0)
		{
			ft_clear(input);
			clearflag = 1;
		}
		// else if (msh.tokens[0] && msh.tokens[0]->type == TOKEN_RE_INPUT)
		// {
		// 	handle_input_redirection(&msh);
		// 	if (split_input[0] && split_input[0][0] == '<')
		// 		non_builtin_redirect_in(&msh);
		// }
		// else if (msh.tokens[0] && msh.tokens[0]->type == TOKEN_RE_OUTPUT)
		// {
		// 	handle_input_redirection(&msh);
		// 	if (split_input[0] && split_input[0][0] != '>')
		// 		non_builtin_redirect(&msh);
		// }
		else
		{
			pipe_check(&msh);
		}
		if (!clearflag)
			add_history(input);
		// if (msh.infile && msh.infile != NULL)
		// {
		// 	free(msh.infile);
		// 	msh.infile = NULL;
		// }
		// if (msh.outfile && msh.outfile != NULL)
		// {
		// 	free(msh.outfile);
		// 	msh.outfile = NULL;
		// }
		free(input);
		free_dpc(split_input);//////////
		free_tokens(msh.tokens); // Free tokens after each iteration
		ft_printf(BRGREEN"Exit Status: %d\n"NO_ALL, msh.exit_status);//////////////
		freeList(msh.cmds);////////////////////////////////
	}
	free_dpc(msh.envp2);
    free_tokens(msh.tokens);
	return (msh.exit_status);
}
