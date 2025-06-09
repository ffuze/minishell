#include "../minishell.h"

void handle_append_redirect(char *filename)
{
    int fd;
    int stdout_backup;
	
	stdout_backup = dup(STDOUT_FILENO);
    if (!filename)
        return;
    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
	{
        ft_printf("error caused by the open function not opening correctly: %s\n", filename);
        perror("open");
        return ;
    }
    ft_printf("file opened successfully, fd: %d\n", fd);
    if (dup2(fd, STDOUT_FILENO) < 0)
	{
        ft_printf("errore causato dalla funzione dup2\n");
        perror("dup2");
        close(fd);
        return ;
    }
	dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);
    close(fd);
}