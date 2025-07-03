/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarino <lemarino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 12:48:16 by lemarino          #+#    #+#             */
/*   Updated: 2025/07/03 11:35:09 by lemarino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Tokenizes a string within single or double quotes whilst preserving the
//  included space characters.
static char	*handle_quotes(char *input, size_t *i, char *word)
{
	size_t	start;
	char	*str_segment;

	start = *i + 1;
	if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
			(*i)++;
	}
	else if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
	}
	str_segment = ft_substr(input, start, *i - start);
	if (!str_segment)
		return (NULL);
	word = ft_strjoin2(word, str_segment);
	free(str_segment);
	if (!word)
		return (NULL);
	return (word);
}

// Assigns TOKEN_WORD to a command and its parameters.
// Strings outside and inside quotes will be joined in the same token
//  if  not separated by at least one space.
// Returns 1 on success, 0 on failure. 
int	tokenize_word(t_token **tokens, char *input, size_t *i, int *count)
{
	size_t	start;
	char	*str_segment;
	char	*word;

	start = *i;
	word = ft_calloc(1, 1);
	while (input[*i] && input[*i] != ' ' && !ft_isoperator(input[*i]))
	{
		start = *i;
		while (input[*i] && input[*i] != ' ' && !ft_isoperator(input[*i]) && \
										input[*i] != '\'' && input[*i] != '"')
			(*i)++;
		str_segment = ft_substr(input, start, *i - start);
		word = ft_strjoin2(word, str_segment);
		free(str_segment);
		if (input[*i] == '\'' || input[*i] == '"')
			word = handle_quotes(input, i, word);
		if (input[*i] == '"' || input[*i] == '\'')
			(*i)++;
	}
	tokens[(*count)++] = make_token(TOKEN_WORD, word, 0, ft_strlen(word));
	return (free(word), 1);
}
