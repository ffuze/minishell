/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:30:24 by adegl-in          #+#    #+#             */
/*   Updated: 2025/04/14 12:01:39 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# define _XOPEN_SOURCE 700

# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

void	ft_echo(char *input);

#endif