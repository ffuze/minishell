#include "../minishell.h"

// Function that reads the input from the heredoc '<<' until the specified limitator
void    read_heredoc(t_msh *msh)
{
	char    *line;
	size_t  len;
	ssize_t nread;
	int     fd;
	char    *delimiter;

	line = NULL;
	len = 0;
	delimiter = NULL;
	int i = 0;
	while (msh->tokens[i])
	{
		if (msh->tokens[i]->type == TOKEN_OUTFILE && msh->tokens[i + 1])
		{
			delimiter = msh->tokens[i + 1]->value;
			break;
		}
		i++;
	}
	if (!delimiter)
	{
		ft_printf("Error: no delimiter found for heredoc\n");
		return;
	}
	fd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf("errore nell'apertura del file here_doc.txt\n");
		return;
	}
	while (1)
	{
		ft_printf("> ");
		nread = getline(&line, &len, stdin);
		if (nread < 0)
			break;
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (strcmp(line, delimiter) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	free(line);
	close(fd);
	fd = open("here_doc.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("errore nell'apertura del file here_doc.txt per la lettura\n");
		return;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_printf("non e' stato salvato il contenuto correttamente\n");
		close(fd);
		unlink("here_doc.txt");
		exit(1);
	}
	close(fd);
}