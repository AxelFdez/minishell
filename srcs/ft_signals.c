#include "../includes/minishell.h"

void	sig_quit(int param)
{
	(void)param;

	if (sig.child == 0 && sig.heredoc == 0)
		write(1, "^\\Quit: 3\n", 10);
	signal(SIGINT, sig_int);
}

void	sig_int(int param)
{
	(void)param;

	if (sig.child == 0 && sig.heredoc == 0)
	{
		write(2, "^C\n", 3);
		//exit(130);
	}
	else if (sig.heredoc == 1)
	{
		sig.int_heredoc = 1;
		write(2, "\n", 1);
	}
	else
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	signal(SIGQUIT, sig_quit);
}

void	signals_func(void)
{
		signal(SIGQUIT, sig_quit);
		signal(SIGINT, sig_int);
}
