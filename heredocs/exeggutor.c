#include "../minishell.h"

// Main function to execute redirections
void execute_redirection(t_msh *msh, t_token **tokens, int i)
{
    if (!tokens[i] || !tokens[i + 1] || i < 0 || !tokens[i + 1]->type || !msh->outfiles)
        return (perror("madonna santissima annunziata"));
    if (msh->outfiles->append_flag && tokens[i + 1]->type == TOKEN_OUTFILE)
        handle_append_redirect(tokens[i + 1]->value);
    // else if (!msh->outfiles->append_flag && tokens[i + 1]->type == TOKEN_LIMITER)
    //     read_heredoc(msh);
}

// // Function to execute a command with redirections
// void execute_command_before_redirection(t_token **tokens, int redirect_pos)
// {
// 	char    **cmd_args;
// 	int     arg_count;
// 	int     i;
// 	pid_t	pid;

// 	arg_count = 0;
// 	i = 0;
// 	while (i < redirect_pos && tokens[i])
// 	{
// 		if (tokens[i]->type == TOKEN_WORD)
// 			arg_count++;
// 		i++;
// 	}
// 	if (arg_count == 0)
// 		return;
// 	cmd_args = malloc((arg_count + 1) * sizeof(char *));
// 	if (!cmd_args)
// 		return;
// 	i = 0;
// 	arg_count = 0;
// 	while (i < redirect_pos && tokens[i])
// 	{
// 		if (tokens[i]->type == TOKEN_WORD)
// 			cmd_args[arg_count++] = tokens[i]->value;
// 		i++;
// 	}
// 	cmd_args[arg_count] = NULL;
// 	if (cmd_args[0])
// 	{
// 		if (ft_strcmp(cmd_args[0], "echo") == 0)
// 			ft_echo(cmd_args);
// 		else if (ft_strcmp(cmd_args[0], "ls") == 0)
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				execvp(cmd_args[0], cmd_args);
// 				perror("execvp");
// 				exit(1);
// 			}
// 			else if (pid > 0)
// 				waitpid(pid, NULL, 0);
// 		}
// 		else
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				execvp(cmd_args[0], cmd_args);
// 				perror("execvp");
// 				exit(1);
// 			}
// 			else if (pid > 0)
// 				waitpid(pid, NULL, 0);
// 		}
// 	}
// 	free(cmd_args);
// }