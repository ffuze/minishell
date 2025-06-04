#include "../minishell.h"

void    handle_append_redirect(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		return;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return;
	}
	close(fd);
}