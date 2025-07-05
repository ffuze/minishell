/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:52:58 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/05 18:59:36 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_msh *msh, char **envp)
{
	msh->backtrackflag = false;
	msh->tokens = NULL;
	msh->envp2 = ft_envp_dup(envp);
	msh->envp2[ft_mtrxlen(msh->envp2)] = ft_strdup("OLDPWD");
	msh->exit_status = 0;
}

void	cleanup_iteration(t_msh *msh)
{
	if (msh->cmds)
	{
		free_cmd_list(msh->cmds);
		msh->cmds = NULL;
	}
	if (msh->tokens)
	{
		free_tokens(msh->tokens);
		msh->tokens = NULL;
	}
	if (msh->exp_input)
	{
		free(msh->exp_input);
		msh->exp_input = NULL;
	}
}

int	process_input(t_msh *msh, char *input)
{
	if (!(*input))
		return (0);
	msh->tokens = tokenize(msh, input);
	if (!msh->tokens || !msh->tokens[0])
	{
		free(msh->exp_input);
		return (0);
	}
	msh->cmds = ft_create_cmd_list(msh, msh->tokens);
	pipe_check(msh);
	cleanup_iteration(msh);
	return (0);
}

static void	get_prompt(t_msh *msh)
{
	char	*input;

	while (1)
	{
		input = readline(BGMAGENTA"pokeshell> "NO_ALL);
		if (!input)
		{
			ft_printf("exit\n");
			return ;
		}
		add_history(input);
		if (process_input(msh, input) == 1)
		{
			free(input);
			return ;
		}
		free(input);
		get_exit_status(msh);
	}
}

int	main(int ac, char *av[], char **envp)
{
	t_msh	msh;

	(void)ac;
	(void)av;
	// print_banner();
	init_shell(&msh, envp);
	if (!msh.envp2)
		return (printf(RED"Failed envp2"NO_ALL), EXIT_FAILURE);
	setup_signals();
	get_prompt(&msh);
	if (msh.tokens)
		free_tokens(msh.tokens);
	free_dpc(msh.envp2);
	return (msh.exit_status);
}
