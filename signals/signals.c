#include "../minishell.h"

volatile sig_atomic_t   sig_received;

sig_received = 0;

// Handle SIGINT signal
void    handle_sigint(int sig)
{
    (void)sig;
    sig_received = 1;
    write(STDOUT_FILENO, "\n", 1);
}