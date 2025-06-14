#include "minishell.h"

void	ft_clear(char *input)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		reset_child_signals();
		char *argv[] = { "clear", NULL };
		execve("/usr/bin/clear", argv, __environ);
		rl_clear_history();
		free(input);	
	}
	else
		wait(NULL);
}

static void	print_token_info(t_msh *msh)
{
	size_t	i;

	i = 0;
	for (size_t i = 0; msh->tokens && msh->tokens[i] != NULL; i++)
		printf("Token numero %zu: %s e' di tipo: %d++\n", i, msh->tokens[i]->value, msh->tokens[i]->type);//////////////
	ft_printf("Number of pipes: %d\n", msh->pipe_count);
}

static int	handle_builtin_commands(t_msh *msh, char **split_input, char *input)
{
	if (ft_strcmp(msh->tokens[0]->value, "exit") == 0)
		return (1);
	else if (ft_strcmp(msh->tokens[0]->value, "export") == 0)
	{
		ft_export(msh, split_input);
		if (!msh->envp2)
			return (-1);
	}
	else if (ft_strcmp(msh->tokens[0]->value, "unset") == 0)
	{
		ft_unset(msh, split_input);
		if (!msh->envp2)
			return (-1);
	}
	else if (ft_strcmp(msh->tokens[0]->value, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(msh->tokens[0]->value, "env") == 0)
		ft_env(msh->envp2);
	else if (ft_strcmp(msh->tokens[0]->value, "cd") == 0)
		ft_cd(msh, split_input);
	else if (ft_strcmp(msh->tokens[0]->value, "echo") == 0)
		ft_echo(split_input);
	else if (ft_strcmp(msh->tokens[0]->value, "clear") == 0)
	{
		ft_clear(input);
		return (2);
	}
	else
		pipe_check(msh);
	return (0);
}

static void	init_shell(t_msh *msh, char **envp)
{
	msh->tokens = NULL;
	msh->envp2 = ft_envp_dup(envp);
}

static void	cleanup_iteration(t_msh *msh, char **split_input, char *input)
{
	free(input);
	free_dpc(split_input);
	free_tokens(msh->tokens);
	ft_printf(BRGREEN"Exit status: %d\n"NO_ALL, msh->exit_status);
	free_cmd_list(msh->cmds);
	free_output_redirection(msh);
}

static int	process_input(t_msh *msh, char *input)
{
	char	**split_input;
	int		builtin_result;
	int		clearflag;

	clearflag = 0;
	if (!(*input))
		return (0);
	split_input = ft_split(input, ' ');
	msh->tokens = tokenize(msh, input);
	print_token_info(msh);
	msh->cmds = ft_create_cmd_list(msh->tokens);
	if (!msh->tokens || !msh->tokens[0])
	{
		free_dpc(split_input);
		return (0);
	}
	builtin_result = handle_builtin_commands(msh, split_input, input);
	if (builtin_result == 1)
	{
		free_everything(*msh, split_input, input);
		free_output_redirection(msh);
		free_cmd_list(msh->cmds);
		return (1);
	}
	if (builtin_result == -1)
	{
		free_everything(*msh, split_input, input);
		ft_putstr_fd(RED"Failed envp2"NO_ALL, 2);
		return (1);
	}
	if (builtin_result == 2)
		clearflag = 1;
	if (!clearflag)
		add_history(input);
	cleanup_iteration(msh, split_input, input);
	return (0);
}

int	main(int ac, char *av[], char **envp)
{
	char	*input;
	t_msh	msh;

	(void)ac;
	av = NULL;
	init_shell(&msh, envp);
	if (!msh.envp2)
		return (printf(RED"Failed envp2"NO_ALL), EXIT_FAILURE);
	setup_signals();
	while (1)
	{
		msh.exit_status = 0;
		input = readline(BGMAGENTA"powershell> "NO_ALL);
		if (!input)
		{
			if (msh.tokens)
				free_tokens(msh.tokens);
			free_dpc(msh.envp2);
			return (EXIT_FAILURE);
		}
		if (process_input(&msh, input) == 1)
			return (EXIT_SUCCESS);
	}
	free_dpc(msh.envp2);
	free_tokens(msh.tokens);
	return (msh.exit_status);
}
