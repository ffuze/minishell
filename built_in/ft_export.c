/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:09:09 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/01 18:09:10 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Copies the old envp to the newly allocated one.
void	envpcpy(char **envp2, char **nenvp, size_t *i)
{
	while (envp2[*i])
	{
		nenvp[*i] = ft_strdup(envp2[*i]);
		if (!nenvp[*i])
		{
			free_dpc(nenvp);
			return ;
		}
		(*i)++;
	}
}

// Adds the new variables to the Environment.
static char	**add_var(char **envp, char *new_var)
{
	size_t	new_len;
	size_t	i;
	char	**nenvp;

	i = 0;
	new_len = ft_mtrxlen(envp) + 1;
	nenvp = ft_calloc(new_len + 1, sizeof(envp));
	if (!nenvp)
		return (free_dpc(envp), NULL);
	envpcpy(envp, nenvp, &i);
	if (!nenvp)
		return (free_dpc(envp), NULL);
	nenvp[i] = ft_strdup(new_var);
	if (!nenvp[i])
		return (free_dpc(nenvp), free_dpc(envp), NULL);
	return (free_dpc(envp), nenvp);
}

// Checks whether the new Variable already exists, if so it overwrites it.
static bool	check_vardup(char **envp2, char *input)
{
	int		i;
	char	*new_var;

	i = 0;
	new_var = ft_before_chr(input, '=');
	while (envp2[i])
	{
		if (ft_strnstr(envp2[i], new_var, ft_strlen(new_var)))
		{
			free(envp2[i]);
			envp2[i] = ft_strdup(input);
			return (free(new_var), true);
		}
		i++;
	}
	return (free(new_var), false);
}

// Checks whether the new Variable's name is acceptable.
// A var's name cannot start by number or symbol and cannot cointain symbols.
static int	var_name_check(t_msh *msh, char *new_var)
{
	size_t	j;
	char	chr;
	char	*var_name;

	j = 0;
	if (!ft_isalpha(new_var[0]) && new_var[0] != '_')
	{
		msh->exit_status = 1;
		return (false);
	}
	var_name = ft_until_chr(new_var, '=');
	while (var_name[j])
	{
		chr = var_name[j++];
		if (j == ft_strlen(var_name) - 1 && chr == '+')
			break ;
		if ((chr < 'A' || chr > 'Z') && (chr < 'a' || chr > 'z') \
				&& (chr < '0' || chr > '9') && chr != '_' && chr != '=')
		{
			msh->exit_status = 1;
			return (free(var_name), false);
		}
	}
	return (free(var_name), true);
}

int	ft_export(t_msh *msh, char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
		print_declarex(msh->envp2);
	else
	{
		while (cmd[i])
		{
			if (!var_name_check(msh, cmd[i]))
			{
				ft_printfd(2, RED"export: `%s': not a valid identifier\n" \
					NO_ALL, cmd[i]);
				return (1);
			}
			else if (ft_strnstr(cmd[i], "+=", ft_strlen(cmd[i])))
				append_handle(msh, cmd[i]);
			else if (check_vardup(msh->envp2, cmd[i]))
				return (0);
			else
				msh->envp2 = add_var(msh->envp2, cmd[i]);
			i++;
		}
	}
	return (0);
}
