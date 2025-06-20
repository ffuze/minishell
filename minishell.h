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
	TOKEN_STRING_SINGLE, // string with single quotes
	TOKEN_STRING_DOUBLE, // string with double quotes
	TOKEN_PIPE, // --> | <--
	TOKEN_RE_INPUT, // --> '<' o '<<' <--
	TOKEN_INFILE, // input file
	TOKEN_LIMITER,
	TOKEN_RE_OUTPUT, // --> '>' o '>>' <--
	TOKEN_OUTFILE, // output file
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
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_inf
{
	char			*infile;
	bool			heredoc_flag; // 0 for '<', 1 for '<<'.
	bool			heredoc_executed;
}					t_inf;

typedef struct s_outf
{
	char			*outfile;
	bool			append_flag; // 0 for '>', 1 for '>>'.
}					t_outf;

typedef	struct s_msh
{
	char			*exp_input;// 	Input from readline() with expanded vars.
	bool			env_var_flag;// True if at least a var is to be expanded.
	t_token			**tokens;
	t_cmds			*cmds;
	char			**envp2;
	t_inf			*infiles; //   Input files from redirection.
	t_outf			*outfiles; //  Output files from redirection.
	bool			outfi_flag; // Tells whether the output must be redirected.
	int				pipe_count; // Number of pipes.
	int				**fd_mrx; //   Array of FileDescriptors for the pipeline.
	unsigned char	exit_status;
	char			*limiter; //   Signal the end of the input in heredoc.
	// int				clearflag;
}					t_msh;

/*________________________________ tokenizer ________________________________*/
t_token	**tokenize(t_msh *msh, char *input);

// Expands the Environment variables from the input string.
// An error message is diplayed if outer quotes are unclosed.
char	*ft_parse_and_expand(t_msh *msh, char *input);

// Expands environment variables and/or the exit status.
// Return 0 on failure.
int	expand_dollar(t_msh *msh, char *input, size_t *i, size_t *j);

// Searches the var in the environment and returns its value.
char	*find_value(char **envp, char *input, size_t *i);

t_token	*make_token(t_token_enum token_type, char *input, size_t start, \
																size_t end);
int		count_tokens(t_token **tokens);
int		tokenize_quotes(t_token **tokens, char *input, size_t *i);
int		tokenize_word(t_token **tokens, char *input, size_t *i, int *count);
/*int	tokenize_d_q(t_token **tokens, t_token_enum token_type,
													char *input, size_t *i);*/
/*int	tokenize_s_q(t_token **tokens, t_token_enum token_type,
													char *input, size_t *i);*/
int		tokenize_input(t_msh *msh, t_token **tokens, char *input, size_t *i);
int		validate_input_files(t_msh *msh);
int		tokenize_output(t_msh *msh, t_token **tokens, char *input, size_t *i);
// Handles $ sign for environment vars expansion.
int		tokenize_env_var(t_msh *msh, t_token **tokens, char *input, size_t *i);
void	tokenize_commands(t_msh *msh);
int		insert_input(t_msh *msh, t_token **tokens);

// Checks whether the tokenized strngs are acceptable and/or 
//  are associated to the needed token.
bool	check_tokens(t_token **tokens);

/*_________________ tokenizer/quotes_removal _________________*/
// Checks whether there are variables to expand or unclosed quotes.
int		ft_parse_input(t_msh *msh, char *input);

// Returns the string "input" without outer quotes.
char	*ft_cleancpy(t_msh *msh, char *input);

// Returns the number of arguments in the input string.
size_t	count_args(char *input);

/*____________________________ create_cmd_list.c ____________________________*/
// Returns a list of commands and relative arguments given from input.
t_cmds	*ft_create_cmd_list(t_token **tokens);

/*_________________________________ utils.c _________________________________*/
int		skip_spaces(t_token *input, int i);

// Verifies whether the c character is a symbol recognized from bash.
int		ft_isbashprint(int c);
// Verifies whether the c character is printable and an operator.
int		ft_isoperator(int c);

// Duplicates the pointer to Environment Variables.
char	**ft_envp_dup(char **envp);

// Prints an error message in red color.
void	print_err(char *s1, char *err_type);

/*_________________________________ built_in ________________________________*/

int	identify_builtin_commands(t_msh *msh, char **cmd);
int	execute_builtin_commands(t_msh *msh, char **cmd, char *input);

void	ft_exit(t_msh *msh, char *input);

void	ft_clear(char *input);

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
void	execute_single_cmd(t_msh *msh, char *input);

// Executes the given command
void	execute_cmd(t_msh *msh, char **cmd, char **envp, char *input);

/*_______________________________ redirection ______________________________*/
// Fill the infile structure with the appropriate file name, and determines
// wether there is an input file or a heredoc.
int		setup_input_redirection(t_msh *msh);

// Substitutes the standard input with a file.
void	redirect_input(t_msh *msh);

// Fills the outfile structure with the appropriate file name, and determines
// whether to overwrite or append the content.
int		setup_output_redirection(t_msh *msh);

// Substitutes the standard output with a file.
void	redirect_output(t_msh *msh);

/*__________________________________ pipes __________________________________*/
// Determines whether a single command or more have to be executed.
void	pipe_check(t_msh *msh, char *input);

// Closes all file descriptors and liberates the allocated memory
void	liberate_fdmatrix(int **fd_mrx, int pipe_count);

// Creates an FD for each pipe in the command line.
int		**fd_matrix_creator(int pipe_count);

// Initializes the first command in the pipeline.
void	init_firstcmd(t_msh *msh, t_cmds *current, int *i, char *input);

// Initializes the last command in the pipeline.
void	init_lastcmd(t_msh *msh, t_cmds *current, int *i, char *input);

// Creates a child process and a pipe for each command to be executed
//  between the first and last.
int		middle_child_generator(t_msh *msh, t_cmds *current, char *input);

/*_______________________________ test_setup.c ______________________________*/
t_cmds	*crealista();
void 	printList(t_cmds *head);
void 	freeList(t_cmds *head);

/*_______________________________ free_memory ______________________________*/
void	free_tokens(t_token **tokens);
void    free_everything(t_msh msh, char *input);
void	free_cmd_list(t_cmds *root);
void	free_output_redirection(t_msh *msh);

/*_______________________________ heredocs ______________________________*/
void    read_heredoc(t_msh *msh);
void    handle_append_redirect(char *filename);
void	execute_command_before_redirection(t_token **tokens, int redirect_pos);
void	execute_redirection(t_msh *msh, t_token **tokens, int i);

/*_______________________________ signals ______________________________*/
void	setup_signals();
void	reset_child_signals();

void	print_banner();

#endif
