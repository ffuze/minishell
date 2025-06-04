#include "../minishell.h"

static int	count_tokens(t_token **tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens[count])
		count++;
	return (count);
}

// Looks for the variable in the Envp and returns it's value to the token.
static t_token	*find_in_env(char **envp, char *var_name)
{
	size_t	i;
	size_t	name_len;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	name_len = ft_strlen(var_name);
	while (envp[i] && ft_strncmp(envp[i], var_name, name_len) != 0)
		i++;
	if (!envp[i])
		return(make_token(TOKEN_WORD, "\0", 1, 1));
	while (envp[i] && envp[i][start++] != '=')
		start++;
	end = start;
	while (envp[i][end])
		end++;
	return (make_token(TOKEN_WORD, envp[i], start, end));
}

// Handles $ sign for environment vars expansion.
int	tokenize_env_var(t_msh *msh, t_token **tokens, char *input, size_t *i)
{
	int		count;
	size_t	start;
	size_t	end;
	char	*var_name;

	count = count_tokens(tokens);
	start = ++(*i);
	while (input[*i] && ft_isbashprint(input[*i]))
		(*i)++;
	end = (*i) - start;
	if (end > 0)
	{
		var_name = ft_substr(input, start, end);
		tokens[count] = find_in_env(msh->envp2, var_name);
		// tokens[count] = make_token(TOKEN_VAR, input, start, end);// SCORRERE NELL'ENV E FARE DIRETAMENTE TOKEN_WORD
		// (*i)++;
	}
	else
		tokens[count] = make_token(TOKEN_WORD, input, start - 1, 1);
	return (1);
}
