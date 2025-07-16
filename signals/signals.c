/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:01:53 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/16 16:45:03 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_signals_prompt(void)
{
	signal(SIGINT, handle_sigint_prompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	setup_signals_exec(void)
{
	signal(SIGINT, handle_sigint_exec);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	setup_signals_heredoc(void)
{
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	reset_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

// WIFEXITED == se il processo e' uscito senza problemi
// WEXITSTATUS == mi salvo l'exit status dopo la terminazione avvenuta con
// successo
// WIFSIGNALED == se il processo e' invece stato interrotto da un segnale
// WTERMSIG == mi salvo il numero del sig che ha ucciso il processo
void	get_exit_status(t_msh *msh)
{
	int		status;
	pid_t	pid;
	int		sig;

	pid = waitpid(-1, &status, WNOHANG);
	if (pid > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				msh->exit_status = 130;
			else if (sig == SIGQUIT)
				msh->exit_status = 131;
			else
				msh->exit_status = 128 + sig;
		}
	}
}
