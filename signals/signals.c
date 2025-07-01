/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:55:42 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/01 21:24:43 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// static void	handle_sigquit(int sig)
// {
// 	(void)sig;
// }

void	setup_signals()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_child_signals()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
