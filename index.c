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
	ft_printf("Number of pipes: %d\n", msh->pipe_number);
}

static void	init_shell(t_msh *msh, char **envp)
{
	msh->tokens = NULL;
	msh->envp2 = ft_envp_dup(envp);
	msh->exit_status = 0;
}

static void	cleanup_iteration(t_msh *msh)
{
	free_tokens(msh->tokens);
	free(msh->exp_input);
	ft_printf(BRGREEN"Exit status: %d\n"NO_ALL, msh->exit_status);
	free_cmd_list(msh->cmds);
}

static int	process_input(t_msh *msh, char *input)
{
	if (!(*input))
		return (0);
	msh->tokens = tokenize(msh, input);
	free(input);
	if (!msh->tokens || !msh->tokens[0])
	{
		free(msh->exp_input);
		return (0);
	}
	if (!validate_input_files(msh))
        return (0);
	print_token_info(msh);
	msh->cmds = ft_create_cmd_list(msh->tokens);
	pipe_check(msh, msh->exp_input);
	add_history(msh->exp_input);
	cleanup_iteration(msh);
	return (0);
}

int	main(int ac, char *av[], char **envp)
{
	char	*input;
	t_msh	msh;

	(void)ac;
	av = NULL;
	// print_banner();
	init_shell(&msh, envp);
	if (!msh.envp2)
		return (printf(RED"Failed envp2"NO_ALL), EXIT_FAILURE);
	setup_signals();
	while (1)
	{
		// msh.exit_status = 0;
		input = readline(BGMAGENTA"pokeshell> "NO_ALL);
		if (!input)
		{
			if (msh.tokens)
				free_tokens(msh.tokens);
			free_dpc(msh.envp2);
			return (EXIT_FAILURE);
		}
		if (process_input(&msh, input) == 1)
			return (EXIT_SUCCESS);
		get_exit_status(&msh);
	}
	free_dpc(msh.envp2);
	free_tokens(msh.tokens);
	return (msh.exit_status);
}
