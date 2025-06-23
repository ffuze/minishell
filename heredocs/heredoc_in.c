#include "../minishell.h"

// Function that reads the input from the heredoc '<<' 
// until the specified delimitator
void read_heredoc(char *delimiter)
{
	char    *line;
	size_t  len;
	ssize_t nread;
	int     fd;

	if (!delimiter)
	{
		ft_printf("Error: no delimiter found for heredoc\n");
		return;
	}
	ft_printf("Heredoc delimiter: '%s'\n", delimiter);
	line = NULL;
	len = 0;
	fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf("An error has occured while opening file heredoc.txt\n");
		return;
	}
	while (1)
	{
		ft_printf("heredoc> ");
		nread = getline(&line, &len, stdin);
		if (nread < 0)
			break;
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			ft_printf("Delimiter '%s' found\n", delimiter);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	free(line);
	close(fd);
	fd = open("here_doc.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("A reading error has occured while opening file heredoc.txt\n");
		return;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_printf("Content not saved properly\n");
		exit(1);
	}
	unlink("here_doc.txt");
	close(fd);
}