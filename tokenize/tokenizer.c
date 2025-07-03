/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <adegl-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:19:53 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/03 17:08:19 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_fill_tokens(t_msh *msh, t_token **tokens, int *count)
{
	size_t	i;

	i = 0;
	while (msh->exp_input[i])
	{
		while (msh->exp_input[i] == ' ')
			i++;
		if (!msh->exp_input[i])
			break ;
		else if (msh->exp_input[i] == '|')
		{
			tokens[(*count)++] = make_token(TOKEN_PIPE, msh->exp_input, i, 1);
			i++;
			msh->pipe_number++;
		}
		else if (msh->exp_input[i] == '<')
			*count += tokenize_input(msh, tokens, msh->exp_input, &i);
		else if (msh->exp_input[i] == '>')
			*count = tokenize_output(msh, tokens, msh->exp_input, &i);
		else
			tokenize_word(tokens, msh->exp_input, &i, count);
	}
}

t_token	**tokenize(t_msh *msh, char *input)
{
	t_token	**tokens;
	int		count;

	count = 0;
	msh->pipe_number = 0;
	msh->exp_input = ft_parse_and_expand(msh, input);
	if (!msh->exp_input)
		return (NULL);
	tokens = ft_calloc((count_args(input) + 2), sizeof(t_token *));
	if (!tokens)
		return (free(msh->exp_input), NULL);
	ft_fill_tokens(msh, tokens, &count);
	tokens[count] = NULL;
	if (!check_tokens(tokens))
	{
		msh->exit_status = 2;
		return (free_tokens(tokens), NULL);
	}
	return (tokens);
}
