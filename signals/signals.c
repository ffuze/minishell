/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alek <alek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:55:42 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/07 03:58:14 by alek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_signal_mode	g_signal_mode = SIG_BACKTOBACK;

static void	handle_sigint(int sig)
{
	t_signal_mode	prev_mode;
	
	(void)sig;
	prev_mode = g_signal_mode;
	g_signal_mode = SIG_INT_RECEIVED;
	if (prev_mode == SIG_BACKTOBACK)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (prev_mode == SIG_COMMAND)
		write(STDOUT_FILENO, "\n", 1);
	else if (prev_mode == SIG_HEREDOC)
		write(STDOUT_FILENO, "\n", 1);
}

// static void	handle_sigquit(int sig)
// {
// 	(void)sig;

// 	return ;
// }

void	setup_signals(t_signal_mode mode)
{
	g_signal_mode = mode;
	
	if (mode == SIG_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
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

void	check_signal_exit_status(t_msh *msh)
{
	if (g_signal_mode == SIG_INT_RECEIVED)
	{
		msh->exit_status = 130;
		g_signal_mode = SIG_BACKTOBACK;
	}
}
