#include "../includes/minishell.h"

void handle_signals(int sig)
{
	if (sig == 2)
	{
		ft_putchar(8);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
// 	if (sig == 3)
// 	{
// 		signal(SIGSTOP, SIG_IGN);
// 		//kill(pid, SIGCONT);
// 	}
}

void signals_(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_signals;
	sa.sa_flags = SA_RESTART;
	sigaddset(&sa.sa_mask, SIGINT);
	// sigaddset(&sa.sa_mask, SIGSTOP);
	// sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGQUIT, &sa, NULL);
	// sigaction(SIGSTOP, &sa, NULL);
}