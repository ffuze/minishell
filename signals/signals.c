#include "../minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// static void	handle_sigquit(int sig)
// {
// 	(void)sig;
// }

void	setup_signals()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_child_signals()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	get_exit_status(t_msh *msh)
{
	int	status;
	pid_t pid;

	pid = waitpid(-1, &status, WNOHANG);
	if (pid > 0)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
	}
}