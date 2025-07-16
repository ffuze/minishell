/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <adegl-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:13:19 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/16 16:33:31 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_sigint_rec = 0;

void	handle_sigint_prompt(int sig)
{
	(void)sig;
	g_sigint_rec = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_exec(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

// ioctl(STDIN_FILENO, TIOCSTI, "\n") gives a newline as input to the 
//  heredoc's readline.
void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sigint_rec = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
}
