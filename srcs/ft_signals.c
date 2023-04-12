#include "../includes/minishell.h"

void handle_signals(int sig)
{
	if (sig == 2)
	{
		//ft_putchar('\b');
		// ft_putchar(-1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "\n", 1);
		ft_putstr("minishell -> ");
		// rl_on_new_line();
		// rl_replace_line("minishell -> ", 0);
		// rl_redisplay();
		// rl_replace_line("minishell -> ", 0);
		// rl_redisplay();
	}
}

void handle_signals_heredoc(int sig)
{
	if (sig == 2)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, "\n", 1);
		exit(1);
	}
}

void signals_(int heredoc)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	if (heredoc == 0)
		sa.sa_handler = handle_signals;
	else
		sa.sa_handler = handle_signals_heredoc;
	sa.sa_flags = SA_RESTART;
	sigaddset(&sa.sa_mask, SIGINT);
	// sigaddset(&sa.sa_mask, SIGSTOP);
	// sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGQUIT, &sa, NULL);
	// sigaction(SIGSTOP, &sa, NULL);
}