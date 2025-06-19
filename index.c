#include "minishell.h"

static void	print_token_info(t_msh *msh)
{
	int	i;

	i = 0;
	if (!msh || !msh->tokens)
		return ;
	while (msh->tokens[i] != NULL)
	{
		if (!msh->tokens[i]->value)
			break ;
		printf("Token numero %d: %s e' di tipo: %d++\n", i, msh->tokens[i]->value, msh->tokens[i]->type);//////////////
		i++;
	}
	ft_printf("Number of pipes: %d\n", msh->pipe_count);
}

/* static int	identify_builtin_commands(t_msh *msh, char **split_input, char *input)
{
	if (ft_strcmp(msh->tokens[0]->value, "env") == 0)
		ft_env(msh->envp2);
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
	else if (ft_strcmp(msh->tokens[0]->value, "cd") == 0)
		ft_cd(msh, split_input);
	else if (ft_strcmp(msh->tokens[0]->value, "echo") == 0)
		ft_echo(split_input);
	else if (ft_strcmp(msh->tokens[0]->value, "clear") == 0)
	{
		ft_clear(input);
		return (2);
	}
	else if (ft_strcmp(msh->tokens[0]->value, "exit") == 0)
		return (1);
	else
		pipe_check(msh);
	return (0);
} */

static void	init_shell(t_msh *msh, char **envp)
{
	msh->tokens = NULL;
	msh->envp2 = ft_envp_dup(envp);
}

static void	cleanup_iteration(t_msh *msh, char *input)
{
	free(input);
	free_tokens(msh->tokens);
	ft_printf(BRGREEN"Exit status: %d\n"NO_ALL, msh->exit_status);
	free_cmd_list(msh->cmds);
	free_output_redirection(msh);
}

static int	process_input(t_msh *msh, char *input)
{
	// char	**split_input;
	// int		builtin_result;

	if (!(*input))
		return (0);
	// split_input = ft_split(input, ' ');
	msh->tokens = tokenize(msh, input);
	if (!msh->tokens)
		return (0);
	if (!validate_input_files(msh))
        return (0);
	print_token_info(msh);
	msh->cmds = ft_create_cmd_list(msh->tokens);
	if (!msh->tokens || !msh->tokens[0])
	{
		// free_dpc(split_input);
		return (0);
	}
	pipe_check(msh, input);
	// if (!msh->clearflag)// perche' non aggiungere clear alla history? perche avevo due neuroni attivi quando ho inserito queste due righe di codice
	add_history(input);
	cleanup_iteration(msh, input);
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
