#include "../minishell.h"

// Main function to execute redirections
void execute_redirection(t_msh *msh, t_token **tokens, int i)
{
    if (!tokens[i] || !tokens[i + 1])
        return;
        
    if (msh->outfiles->append_flag && tokens[i + 1]->type == TOKEN_OUTFILE)
        handle_append_redirect(tokens[i + 1]->value);
    else if (!msh->outfiles->append_flag && tokens[i + 1]->type == TOKEN_INFILE)    
        read_heredoc(msh);
}

// // Function to execute a command with redirections
// void execute_command_with_redirections(t_msh *msh, t_token **tokens)
// {
//     int        i;
//     char    **cmd_args;
//     int     arg_count;
    
//     arg_count = 0;
//     i = 0;
//     while (tokens[i])
//     {
//         if (tokens[i]->type == TOKEN_WORD)
//             arg_count++;
//         i++;
//     }
//     cmd_args = malloc((arg_count + 1) * sizeof(char *));
//     if (!cmd_args)
//         return;
//     i = 0;
//     arg_count = 0;
//     while (tokens[i])
//     {
//         if (tokens[i]->type == TOKEN_WORD)
//             cmd_args[arg_count++] = tokens[i]->value;
//         i++;
//     }
//     cmd_args[arg_count] = NULL;
//     if (cmd_args[0])
//     {
//         if (ft_strcmp(cmd_args[0], "echo") == 0)
//             ft_echo(cmd_args);
//         else
//         {
//             // Esegui comando esterno
//             execvp(cmd_args[0], cmd_args);
//             perror("execvp");
//         }
//     }
//     free(cmd_args);
// }