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
	TOKEN_RE_INPUT, // --> '<' o '<<' <--
	TOKEN_INFILE, // input file
	TOKEN_RE_OUTPUT, // --> '>' o '>>' <--
	TOKEN_OUTFILE, // output file
	TOKEN_LIMITER,
	TOKEN_ERROR // invalid token
}	t_token_enum;

typedef struct s_token
{
	t_token_enum	type;
	char			*value;
}					t_token;

typedef struct s_cmds
{
	char			**cmd;
	// int				pipefd[2];
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_inf
{
	char			*infile;
	bool			heredoc_flag; // 0 for '<', 1 for '<<'.
	char			*limiter; // Signal the end of the input in heredoc.
	struct s_inf	*next;
}					t_inf;

typedef struct s_outf
{
	char			*outfile;
	bool			append_flag; // 0 for '>', 1 for '>>'.
	struct s_outf	*next;
}					t_outf;

typedef	struct s_msh
{
	t_token			**tokens;
	t_cmds			*cmds;
	char			**envp2;
	t_inf			*infiles; //   Input files from redirection.
	t_outf			*outfiles; //  Output files from redirection.
	bool			outfi_flag; // Tells whether the output must be redirected.
	unsigned int	pipe_count; // Number of pipes.
	int				**fd_mrx;
	// int				pipefd[2];
	bool			pipeflag; //   Tells whether a pipe has been opened. 
	unsigned char	exit_status;
}					t_msh;

/*_______________________________ tokenizer _________________________________*/
t_token	**tokenize(t_msh *msh, char *input);
t_token	*make_token(t_token_enum token_type, char *input, size_t start, \
	size_t end);
int		tokenize_input(t_msh *msh, t_token **tokens, char *input, size_t *i);
int		tokenize_output(t_msh *msh, t_token **tokens, char *input, size_t *i);
void	tokenize_commands(t_msh *msh);

/*_______________________ utils.c _______________________*/
int		skip_spaces(t_token *input, int i);

// Verifies that the c character is not a symbol recognized from bash.
int		ft_isbashprint(int c);

// Duplicates the pointer to Environment Variables.
char	**ft_envp_dup(char **envp);

// Prints an error message in red color.
void	print_err(char *s1, char *err_type);

/*_______________________________ built_in ______________________________*/

void	ft_echo(char  **cmd);

// Prints the absolute path to the current directory.
void	ft_pwd();

// Prints all the environment variables.
void	ft_env(char **envp2);

// Adds the arguments to the environment as new variables.
// Prints Environment Vars in ASCII order if no arguments are given.
void	ft_export(t_msh *msh, char  **cmd);
// Handles the "+=" option for export.
void	append_handle(t_msh *msh, char *var);
// Copies the old envp to the newly allocated one.
void	envpcpy(char **envp2, char **nenvp, size_t *i);

// Prints Environment Vars in ASCII order with their value in double quotes.
void	print_declarex(char **envp2);

// Removes Variables from the Environment.
void	ft_unset(t_msh *msh, char  **cmd);

// Canghes the current directory.
void	ft_cd(t_msh *msh, char  **cmd);

/*________________________________ non_builtin ______________________________*/
// Initializes a non built-in command.
void	execute_single_cmd(t_msh *msh);

// Executes the given command
void	*execute_cmd(char **cmd, char **envp);

/*_______________________________ redirection ______________________________*/
int		handle_input_redirection(t_msh *msh);
void	redirect_input(t_msh *msh);

/*__________________________________ pipes __________________________________*/
// Determines whether a single command or more have to be executed.
void	pipe_check(t_msh *msh);

// Closes all file descriptors and liberates the allocated memory
void	liberate_fdmatrix(int **fd_mrx, int pipe_count);

// Creates an FD for each pipe in the command line.
int	**fd_matrix_creator(int pipe_count);

int	first_cmd_process(t_msh *msh, int *pipefd);
int	last_cmd_process(char **cmd, char **envp, int *pipefd);

// Creates a child process and a pipe for each command to be executed
//  between the first and last.
int	middle_child_generator(t_msh *msh);

/*_______________________________ test_setup.c ______________________________*/
t_cmds	*crealista();
void printList(t_cmds *head);
void freeList(t_cmds *head);

/*_______________________________ free_memory ______________________________*/
void	free_tokens(t_token **tokens);
void    free_everything(t_msh msh, char **split_input, char *input);
void    free_infiles(t_inf *infiles);

#endif
