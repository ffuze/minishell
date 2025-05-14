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
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MACROS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~COLORS~~~~~~~~~~~~~~~*/
# define NO_ALL "\033[0m"

# define NO_COLOR "\e[39m"
# define BLACK "\e[30m"
# define RED "\033[31m"
# define GREEN "\e[32m"
# define BRGREEN "\033[32;1m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[95m"
# define BRCYAN "\033[96m"

/*~~~~~~~~~~~~BACKGROUNDS~~~~~~~~~~~~~*/
# define BGMAGENTA "\033[45m"
# define BLACK_ON_WHITE "\e[107;30m"
# define NO_BG "\e[49m"

/*~~~~~~~~~~~~~~~MORE~~~~~~~~~~~~~~~*/
# define BOLD "\e[1m"// "\e[1;4m" Bold and Underlined
# define NO_BOLD "\e[21m"

# define UNDERLINE "\e[4m"
# define NO_UNDERLINE "\e[24m"

# define BLINK "\e[5m"//Doesn't work on vscode terminal
# define NO_BLINK "\e[25m"

# define HIDE "\e[8m"
# define NO_HIDE "\e[28m"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum s_token_enum
{
	TOKEN_WORD, // simple strings
    TOKEN_VAR, // all variables starting with the $
    TOKEN_STRING_SINGLE, // string with single quotes
    TOKEN_STRING_DOUBLE, // string with double quotes
    TOKEN_PIPE, // --> | <--
	TOKEN_RE_INPUT, // --> '<' <--
	TOKEN_INFILE, // input file
	TOKEN_RE_OUTPUT, // --> '>' <--
	TOKEN_OUTFILE, // output file
    TOKEN_HEREDOC, // --> '>>'
	TOKEN_OUTAPPEND,
	TOKEN_LIMITER,
	TOKEN_ERROR // invalid token
}	t_token_enum;

typedef struct s_token
{
	t_token_enum	type;
	char			*value;
}	t_token;

// typedef struct s_cmds
// {
// 	char	**cmd;
// 	t_cmds 	*next;
// }	t_cmds;

typedef	struct s_msh
{
	t_token			**tokens;
	char			**cmds;
	char			**envp2;
	unsigned char	exit_status;
	char			*infile;
	char			*outfile;
	char			*limiter;
	int				pipe_count;
}	t_msh;

/*                   tokenizer.c                 */
t_token	**tokenize(char *input);


/*                   utils.c                 */
int		skip_spaces(t_token *input, int i);

// Verifies that the c character is not a symbol recognized from bash.
int     ft_isbashprint(int c);

// Duplicates the pointer to Environment Variables.
char	**ft_envp_dup(char **envp);


/*                   ft_echo.c                 */
void	ft_echo(char  **cmd);


/*                   ft_pwd.c                 */
// Prints the absolute path to the current directory.
void	ft_pwd();


/*                   ft_env.c                 */
// Prints all the environment variables.
void	ft_env(char **envp2);

/*                   ft_export.c                 */
// Adds the arguments to the environment as new variables.
// Prints Environment Vars in ASCII order if no arguments are given.
void	ft_export(t_msh *msh, char  **cmd);

/*                    ft_unset                   */
// Removes Variables from the Environment.
void	ft_unset(t_msh *msh, char  **cmd);

/*                    ft_cd.c                     */
// Canghes the current directory.
void	ft_cd(t_msh *msh, char  **cmd);

/*                    ft_cd.c                     */
// Initializes non built-in commands.
void	non_builtin(t_msh *msh, char  **cmd);

#endif
