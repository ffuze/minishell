/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:04:26 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:32 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_plus(char *new_var)
{
	int		i;
	int		j;
	char	*clean_var;

	i = 0;
	clean_var = ft_calloc(ft_strlen(new_var), 1);
	if (!clean_var)
		return (NULL);
	while (new_var[i] && new_var[i] != '+')
	{
		clean_var[i] = new_var[i];
		i++;
	}
	j = i;
	i++;
	while (new_var[i])
	{
		clean_var[j++] = new_var[i];
		i++;
	}
	return (clean_var);
}

// Adds the new variable to the Environment.
static char	**add_var(char **envp, char *new_var)
{
	size_t	new_len;
	size_t	i;
	char	*clean_var;
	char	**nenvp;

	i = 0;
	new_len = ft_mtrxlen(envp) + 1;
	nenvp = ft_calloc(new_len + 1, sizeof(envp));
	if (!nenvp)
		return (free_dpc(envp), NULL);
	envpcpy(envp, nenvp, &i);
	if (!nenvp)
		return (free_dpc(envp), NULL);
	clean_var = remove_plus(new_var);
	if (!clean_var)
		return (free_dpc(nenvp), free_dpc(envp), NULL);
	nenvp[i] = ft_strdup(clean_var);
	if (!nenvp[i])
		return (free(clean_var), free_dpc(nenvp), free_dpc(envp), NULL);
	return (free(clean_var), free_dpc(envp), nenvp);
}

// Checks whether the new Variable already exists, if so it overwrites it.
static bool	check_vardup(char **envp2, char *input)
{
	int		i;
	char	*new_var;
	char	*new_var_name;

	i = 0;
	new_var_name = ft_until_chr(input, '+');
	if (!new_var_name)
		return (print_err("check_vardup: ", "first malloc failed\n"), false);
	new_var = ft_substr(input, 0, ft_strlen(new_var_name) - 1);
	if (!new_var)
		return (print_err("check_vardup: ", "second malloc failed\n"), \
					free(new_var_name), false);
	free(new_var_name);
	while (envp2[i])
	{
		if (ft_strnstr(envp2[i], new_var, ft_strlen(new_var)))
			return (free(new_var), true);
		i++;
	}
	return (free(new_var), false);
}

static void	append_var(char **envp2, char *var)
{
	size_t	i;
	char	*var_name;
	char	*tmp;

	i = 0;
	tmp = ft_until_chr(var, '+');
	var_name = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	free (tmp);
	while (envp2[i])
	{
		if (ft_strnstr(envp2[i], var_name, ft_strlen(var_name)))
		{
			tmp = ft_strdup(envp2[i]);
			free(envp2[i]);
			envp2[i] = ft_strjoin(tmp, ft_strchr2(var, '='));
			return (free(var_name), free(tmp));
		}
		i++;
	}
}

void	append_handle(t_msh *msh, char *var)
{
	if (check_vardup(msh->envp2, var))
		append_var(msh->envp2, var);
	else
		msh->envp2 = add_var(msh->envp2, var);
}
